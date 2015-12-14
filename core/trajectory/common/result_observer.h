#pragma once

#include <network_dynamics.h>
#include <node_chooser.h>
#include "thread_pool.h"

#include <list>
#include <iostream>
#include <fstream>

class result_observer
{
public:
  typedef network_dynamics::state_type state_type;

public:
  virtual void process(const state_type& r, const double t) = 0;
};

class stream_dumper : public result_observer
{
public:
  enum class format_type
  {
    empty,
    raw,
    gnuplot
  };

  stream_dumper(format_type format = format_type::empty, std::ostream& out = std::cout);
  virtual void process(const state_type& r, const double t) override;

private:
  void format_for_raw(const state_type& state, const double t);
  void format_for_gnuplot(const state_type& state, const double t);

protected:
  format_type format_;
  std::ostream& out_;
};

class file_dumper : public result_observer
{
public:
  file_dumper(const std::string& filepath, stream_dumper::format_type format = stream_dumper::format_type::raw);
  ~file_dumper();
  virtual void process(const state_type& r, const double t) override;

private:
  std::ofstream out_;
  stream_dumper dumper_;
};

class trajectory_dumper : public result_observer
{
public:
  trajectory_dumper(std::ostream& out, const network::node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const std::size_t step);
  virtual void process(const state_type& r, const double t) override;

private:
  std::ostream& out_;
  network::node_positions_type initial_positions_;
  node_chooser::node_numbers_type nodes_;
  std::size_t step_;
};

class stability_checker : public result_observer
{
public:
  stability_checker(const network::node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes);
  virtual void process(const state_type& r, const double t) override;

private:
  network::node_positions_type initial_positions_;
  node_chooser::node_numbers_type nodes_;
};

class composite_result_observer : public result_observer
{
public:
  composite_result_observer();
  virtual void process(const state_type& r, const double t) override;
  void add_result_observer(const std::shared_ptr<result_observer>& observer);

private:
  std::list<std::shared_ptr<result_observer>> observers_;
};

class bg_thread_handler
{
public:
  bg_thread_handler();
  ~bg_thread_handler();
  void add_future(std::future<void>&& f);

private:
  thread_pool pool_;
  std::vector<std::future<void>> futures_;
};

class result_observer_wrapper
{
public:
  typedef result_observer::state_type state_type;

public:
  result_observer_wrapper(const network_dynamics_wrapper& dynamics);
  void operator()(const state_type& r, const double t);
  void set_result_observer(const std::shared_ptr<result_observer>& observer);

private:
  network_dynamics_wrapper dynamics_;
  std::shared_ptr<result_observer> observer_;
  std::shared_ptr<bg_thread_handler> bg_handler_;
};
