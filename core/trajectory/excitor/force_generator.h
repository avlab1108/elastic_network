/**
 * @file force_generator.h
 * @brief This file contains @ref force_generator class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <common_types.h>

#include <vector>

/**
 * @class force_generator
 * @brief Generates vector of random forces with fixed summary magnitude.
 */
class force_generator
{
public:
  /**
   * @brief Constructs generator with summary magnitude @a fs for nodes @a nodes.
   *
   * @param fs Summary magnitude of forces.
   * @param nodes Node indexes for which forces are generated.
   */
  force_generator(const forces_spec& fspec);

  /**
   * @brief Generates random forces.
   *
   * @return Generated forces.
   */
  forces_type generate();

private:
  void generate_forces();

private:
  /// Forces specification.
  const forces_spec fspec_;
  /// Resulting forces.
  forces_type result_;
};
