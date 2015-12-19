/**
 * @file force_generator.h
 * @brief This file contains @a force_generator class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <point.h>

#include <vector>

/**
 * @class force_generator
 * @brief Generates vector of random forces with fixed summary magnitude.
 */
class force_generator
{
public:
  /// Force type.
  typedef point_type force_type;
  /// Container for nodes.
  typedef std::vector<std::size_t> nodes_type;
  /// Container for generated forces.
  typedef std::vector<std::pair<std::size_t, force_type>> result_type;

  /**
   * @brief Constructs generator with summary magnitude @a fs for nodes @a nodes.
   *
   * @param fs Summary magnitude of forces.
   * @param nodes Node indexes for which forces are generated.
   */
  force_generator(const double fs, const nodes_type& nodes);

  /**
   * @brief Generates random forces.
   *
   * @return Generated forces.
   */
  result_type generate();

private:
  /// Summary magnitude.
  const double fs_;
  /// Nodes.
  const nodes_type nodes_;
};
