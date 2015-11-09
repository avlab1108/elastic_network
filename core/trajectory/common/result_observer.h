#pragma once

#include <network_dynamics.h>

#include <iostream>

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

  stream_dumper(format_type format = format_type::empty, std::ostream* out = &std::cout);

  virtual void process(const state_type& r, const double t) override;

private:
  void format_for_raw(const state_type& state, const double t);
  void format_for_gnuplot(const state_type& state, const double t);

protected:
  format_type format_;
  std::ostream* out_;
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
  std::shared_ptr<result_observer> observer_;
  network_dynamics_wrapper dynamics_;
};
