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
