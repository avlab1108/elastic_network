/**
 * @file common_types.h
 * @brief This file contains common typedefs and types, used across all modules.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "point.h"

#include <vector>

/// Point type (3d-vector)
typedef point<double, 3> point_type;

/// State of network dynamics.
typedef std::vector<point_type> state_type;

/// Node positions container.
typedef std::vector<point_type> node_positions_type;

/// Links container.
typedef std::vector<std::pair<std::size_t, std::size_t>> links_type;

/// Forces type.
typedef std::vector<std::pair<std::size_t, point_type>> forces_type;

/**
 * @struct forces_spec
 * @brief Desribes random forces for excitation process.
 */
struct forces_spec
{
  /**
   * @brief Constructs forces specification from specified params.
   * @param fs_value Summary magnitude of forces.
   * @param nodes_list Force application odes.
   * @param dynamic_forces Dynamic forces.
   */
  explicit forces_spec(const double fs_value, const std::vector<std::size_t>& nodes_list = std::vector<std::size_t>(), const bool dynamic_forces = false) :
    fs(fs_value),
    nodes(nodes_list),
    dynamic(dynamic_forces)
  {}

  /// Summary magnitude of forces.
  double fs;
  /// Force application nodes.
  std::vector<std::size_t> nodes;
  /// Dynamic forces.
  bool dynamic;
};

/**
 * @struct stabilization_spec
 * @brief Describes stabilization for relaxation process.
 */
struct stabilization_spec
{
  /**
   * @brief Constructs stabilization specification from spefied params.
   * @param eps Stabilization epsilon.
   * @param steps Step count.
   * */
  explicit stabilization_spec(const double eps = 1e-9, const std::size_t steps = 10000) :
    epsilon(eps),
    step_count(steps)
  {
  }

  /// Stabilization epsilon.
  double epsilon;
  /// Stabilization step count.
  std::size_t step_count;
};

/**
 * @struct relaxation_time_step_spec
 * @brief Describes integration step specification for relaxation process.
 *
 * Integration step is calculated in the following way: initial step size is @ref step. Then, after each @ref time_delta steps, step is multiplied by @ref coefficient.
 * So, at the time moment i step can be retrieved in the following way: step_value = coefficient ^ (floor(i / time_delta)) * step.  
 */
struct relaxation_time_step_spec
{
  /**
   * @brief Constructs relaxation time step specification from provided parameters.
   * @param step Initial step size.
   * @param delta Time delta.
   * @param coefficient Multiplication coefficient.
   */
  explicit relaxation_time_step_spec(const double step = 1e-2, const std::size_t delta = 10000, const double coeff = 1.0) :
    initial_step(step),
    time_delta(delta),
    coefficient(coeff)
  {
  }

  /// Initial step.
  double initial_step;
  /// Time delta.
  std::size_t time_delta;
  /// Multiplication coefficient.
  double coefficient;
};
