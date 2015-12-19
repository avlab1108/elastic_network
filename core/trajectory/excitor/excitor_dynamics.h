/**
 * @file excitor_dynamics.h
 * @brief This file contains @a excitor_dynamics class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "force_generator.h"

#include <point.h>
#include <network_dynamics.h>

/**
 * @class excitor_dynamics
 * @brief Dynamics with random forces application on nodes.
 */
class excitor_dynamics : public network_dynamics
{
public:
  /// Forces type.
  typedef std::vector<std::pair<std::size_t, point_type>> forces_type;

public:
  /**
   * @brief Constructs dynamics for provided network with specified initial node positions, summary magnitude of random forces and node indexes, to which random forces will be applied.
   *
   * @param net Network.
   * @param initial_positions Initial positions of nodes.
   * @param fs Summary magnitude of random forces.
   * @param nodes Nodes for force application.
   */
  excitor_dynamics(const network& net, const network::node_positions_type& initial_positions, const double fs, const std::vector<std::size_t>& nodes);
  /**
   * @brief Implementation of base class interface. Calculates state of network with provided arguments.
   *
   * @param r State of network.
   * @param drdt Derivative of position by time.
   * @param t Time point.
   */
  virtual void calculate(const state_type& r, state_type& drdt, const double t) override;
  /**
   * @brief Implementation of base class interface. Generates random forces for next step.
   */
  virtual void prepare_for_step() override;

private:
  /// Summary magnitude of forces.
  const double fs_;
  /// Force application nodes.
  const std::vector<std::size_t> nodes_;
  /// Generated forces.
  forces_type forces_;
  /// Force generator.
  force_generator generator_;
};
