/**
 * @file result_observer.h
 * @brief This file contains @ref result_observer, @ref stream_dumper, @ref file_dumper, @ref trajectory_dumper, @ref stability_checker, @ref composite_result_observer and @ref result_observer_wrapper classes.
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
class result_observer
{
public:
  /**
   * @brief Processes step at defined time point.
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
   * @param format Format of output.
   * @param out Output stream.
   */
  stream_dumper(format_type format = format_type::empty, std::ostream& out = std::cout);
  /**
   * @brief Implements interface of base class.
   *        Dumps data to output stream.
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

/**
 * @class file_dumper
 * @brief Dumps results to output file.
 */
class file_dumper : public result_observer
{
public:
  /**
   * @brief Constructs dumper with specified output file and format.
   * @param filepath Output file name.
   * @param format Format of output file.
   */
  file_dumper(const std::string& filepath, stream_dumper::format_type format = stream_dumper::format_type::raw);
  /**
   * @brief Destructor to flush/close file.
   */
  ~file_dumper();
  /**
   * @brief Implements interface of base class.
   *        Dumps data to output file.
   *
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) override;

private:
  /// Output file stream.
  std::ofstream out_;
  /// Stream dumper for formatting output.
  stream_dumper dumper_;
};

/**
 * @class trajectory_dumper
 * @brief Dumps trajectory to output stream.
 */
class trajectory_dumper : public result_observer
{
public:
  /**
   * @brief Constructs dumper from provided parameters.
   * @param out Output stream.
   * @param initial_positions Initial positions of network nodes.
   * @param nodes Node numbers.
   * @param step Step value.
   */
  trajectory_dumper(std::ostream& out, const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const std::size_t step);
  /**
   * @brief Implements interface of base class.
   *        Dumps trajectory info to output stream.
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) override;

private:
  /// Output stream.
  std::ostream& out_;
  /// Stream mutex.
  std::mutex out_mutex_;
  /// Initial positions of network nodes.
  node_positions_type initial_positions_;
  /// Node numbers.
  node_chooser::node_numbers_type nodes_;
  /// Step value.
  std::size_t step_;
};

/**
 * @class stability_checker
 * @brief Checks for stability conditions during relaxation process.
 */
class stability_checker : public result_observer
{
public:
  /**
   * @brief Constructs stability checker from provided parameters.
   * @param initial_positions Initial positions of network nodes.
   * @param nodes Node numbers.
   * @param stab_spec Stabilization specification.
   */
  stability_checker(const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const stabilization_spec stab_spec);
  /**
   * @brief Implements interface of base class.
   *        Checks for stability conditions during relaxation..
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) override;

private:
  /// Initial positions of network nodes.
  node_positions_type initial_positions_;
  /// Node numbers.
  node_chooser::node_numbers_type nodes_;
  /// Current number of stabilized steps.
  std::size_t stabilization_steps_;
  /// Stabilization specification.
  stabilization_spec stab_spec_;
  /// Distance between nodes 0-1 from previous step.
  double previous_dist1_;
  /// Distance between nodes 1-2 from previous step.
  double previous_dist2_;
  /// Distance between nodes 2-0 from previous step.
  double previous_dist3_;
};

/**
 * @class composite_result_observer
 * @brief Allows group of observers to be treated in the same way as single observer.
 */
class composite_result_observer : public result_observer
{
public:
  /**
   * @brief Constructs composite observer.
   */
  composite_result_observer();
  /**
   * @brief Implements interface of base class.
   *        Sequentially calls the same method of all containing observers.
   * @param r State of network.
   * @param t Time point.
   */
  virtual void process(const state_type& r, const double t) override;
  /**
   * @brief Adds net observer to the list of observers.
   * @param observer New observer.
   */
  void add_result_observer(const std::shared_ptr<result_observer>& observer);

private:
  /// Observer list.
  std::list<std::shared_ptr<result_observer>> observers_;
};

/**
 * @class result_observer_wrapper
 * @brief Connection point between @ref result_observer and boost.odeint infrastructure.
 */
class result_observer_wrapper
{
public:
  /**
   * @brief Constructs wrapper over the provided observer.
   * @param dynamics Real observer.
   */
  result_observer_wrapper(const network_dynamics_wrapper& dynamics);
  /**
   * @brief Processes current state of system. Delegates processing to underlying observer.
   * @param r State of network.
   * @param t Time point.
   */
  void operator()(const state_type& r, const double t);
  /**
   * @brief Sets underlying result observer.
   * @param observer Observer.
   */
  void set_result_observer(const std::shared_ptr<result_observer>& observer);

private:
  /// Network dynamics wrapper.
  network_dynamics_wrapper dynamics_;
  /// Real dynamics.
  std::shared_ptr<result_observer> observer_;
};
