/**
 * @file result_observer.h
 * @brief This file contains @a result_observer, @a stream_dumper, @a file_dumper, @a trajectory_dumper, @a stability_checker, @a composite_result_observer and @a result_observer_wrapper classes.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <network_dynamics.h>
#include <node_chooser.h>
#include <common_types.h>

#include <list>
#include <iostream>
#include <fstream>
#include <mutex>

/**
 * @class result_observer
 * @brief Observes result of each step of numerical integration of network dynamics.
 */
  //  }));
class result_observer
{
public:
  /**
   * @brief Processes step at defined time point.
   *
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) = 0;
};

/**
 * @class stream_dumper
 * @brief Dumps results to output stream.
 */
class stream_dumper : public result_observer
{
public:
  /**
   * @enum format_type
   * @brief Describes supported formats of result dumping.
   */
  enum class format_type
  {
    empty,
    raw,
    gnuplot
  };

  /**
   * @brief Constructs stream_dumper object with provided format and stream.
   *
   * @param format Format of output.
   * @param out Output stream.
   */
  stream_dumper(format_type format = format_type::empty, std::ostream& out = std::cout);
  /**
   * @brief Implements interface of base class.
   *        Dumps data to output stream.
   *
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) override;

private:
  /**
   * @brief Formats data for simple textual output.
   *
   * @param state State of network.
   * @param t Time point.
   */
  void format_for_raw(const state_type& state, const double t);
  /**
   * @brief Formats data for output in gnuplot-supported format.
   *
   * @param state State of network.
   * @param t Time point.
   */
  void format_for_gnuplot(const state_type& state, const double t);

protected:
  /// Format of output.
  format_type format_;
  /// Output stream.
  std::ostream& out_;
  /// Output stream lock.
  std::mutex out_mutex_;
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
  trajectory_dumper(std::ostream& out, const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const std::size_t step);
  virtual void process(const state_type& r, const double t) override;

private:
  std::ostream& out_;
  std::mutex out_mutex_;
  node_positions_type initial_positions_;
  node_chooser::node_numbers_type nodes_;
  std::size_t step_;
};

class stability_checker : public result_observer
{
public:
  stability_checker(const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes);
  virtual void process(const state_type& r, const double t) override;

private:
  node_positions_type initial_positions_;
  node_chooser::node_numbers_type nodes_;
  std::size_t stabilization_steps_;
  double previous_dist1_;
  double previous_dist2_;
  double previous_dist3_;
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

class result_observer_wrapper
{
public:
  result_observer_wrapper(const network_dynamics_wrapper& dynamics);
  void operator()(const state_type& r, const double t);
  void set_result_observer(const std::shared_ptr<result_observer>& observer);

private:
  network_dynamics_wrapper dynamics_;
  std::shared_ptr<result_observer> observer_;
};
