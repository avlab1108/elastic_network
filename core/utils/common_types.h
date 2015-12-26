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
   *
   * @param fs_value Summary magnitude of forces.
   * @param nodes_list Force application odes.
   * @param dynamic_forces Dynamic forces.
   */
  forces_spec(const double fs_value, const std::vector<std::size_t>& nodes_list = std::vector<std::size_t>(), const bool dynamic_forces = false) :
    fs(fs_value),
    nodes(nodes_list),
    dynamic(dynamic_forces)
  {}

  /// Summary magnitude of forces.
  const double fs;
  /// Force application nodes.
  const std::vector<std::size_t> nodes;
  /// Dynamic forces.
  const bool dynamic;
};

