/**
 * @file network_dynamics.h
 * @brief This file contains @a network_dynamics class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "network.h"
#include "point.h"

#include <memory>
#include <vector>

/**
 * @class network_dynamics
 * @brief Class represents network dynamics.
 *
 * Dynamics is defined with the following equation: 
 * \f[
 * \frac{d\vec{R}}{dt}=-\sum\limits_{j=1}^{N} A_{ij} \frac{\vec{R_i} - \vec{R_j}}{\left|\vec{R_i} - \vec{R_j}\right|} \left(\left|\vec{R_i} - \vec{R_j}\right| - \left|\vec{R_i^{(0)}} - \vec{R_j^{(0)}}\right| \right)
 * \f]
 * where \f$A\f$ is the adjacency matrix of network.
 * Network node positions at any point of time is calculated through the integration of this equation.
 * This class uses boost.odeint library for numeric integration of mentioned equaiton.
 */
class network_dynamics
{
public:
  /// Current state of system.
  typedef std::vector<point_type> state_type;

public:
  /**
   * @brief Constructs dynamics for provided network and initial positions of nodes.
   *
   * @param net Network.
   * @param initial_positions Initial positions of network nodes.
   */
  network_dynamics(const network& net, const network::node_positions_type& initial_positions);
  /**
   * @brief Calculates value of differential equation's right side based on provided data.
   *
   * @param r State of network.
   * @param drdt Derivative of position vector by the time (left side if equation).
   * @param t Time point.
   */
  virtual void calculate(const state_type& r, state_type& drdt, const double t);

  /**
   * @brief Hook to prepare for step before actually performing it.
   */
  virtual void prepare_for_step();

private:
  /// Network.
  network net_;
  /// Initial positions of nodes.
  network::node_positions_type initial_positions_;
  /// Initial distances between nodes.
  std::vector<std::vector<double>> initial_distances_;
};

/**
 * @class network_dynamics_wrapper
 * @brief Connection point between @a network_dynamics and boost.odeint infrastructure.
 */
class network_dynamics_wrapper
{
public:
  /// State of network.
  typedef network_dynamics::state_type state_type;

public:
  /**
   * Constructs wrapper over the real dynamics calculator @a network_dynamics.
   *
   * @param dynamics Dynamics of network.
   */
  network_dynamics_wrapper(const std::shared_ptr<network_dynamics>& dynamics);
  /**
   * @brief Calculate state of network. Delegates calculation to underlying dynamics.
   *
   * @param r State of network.
   * @param drdt Derivative of position vector by the time.
   * @param t Time point.
   */
  void operator() (const state_type& r, state_type& drdt, const double t);

  /**
   * @brief Hook to prepare for step before actually performing it. Delegates to underlying dynamics.
   */
  void prepare_for_step();

private:
  /// Dynamics of network.
  std::shared_ptr<network_dynamics> dynamics_;
};

typedef std::shared_ptr<network_dynamics> network_dynamics_ptr;
