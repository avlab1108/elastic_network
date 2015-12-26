/**
 * @file trajectory_worker.h
 * @brief This file contains @a trajectory_worker class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "result_observer.h"

#include <network.h>
#include <common_types.h>

#include <memory>

class network_dynamics;

/**
 * @class trajectory_worker
 * @brief Base class of all classes which should generate trajectory or trajectory part.
 */
class trajectory_worker
{
protected:
  /**
   * @brief Constructs trajectory worker for specified network with initial positions and provided dynamics.
   *
   * @param net Network.
   * @param initial_positions Initial positions of nodes.
   * @param dynamics Dynamics of network.
   */
  trajectory_worker(network& net, const node_positions_type& ininital_positions, const std::shared_ptr<network_dynamics>& dynamics);

public:
  /**
   * @brief Sets observer for results. @a observer will be be called after each step of process.
   *
   * @param observer Result observer.
   */
  void set_result_observer(const std::shared_ptr<result_observer>& observer);

  /**
   * @brief Performs process of current worker.
   */
  virtual void run() = 0;

protected:
  /// Network.
  network& net_;
  /// Initial node positions.
  node_positions_type initial_positions_;
  /// Network dynamics.
  network_dynamics_wrapper dynamics_;
  /// Result observer.
  result_observer_wrapper observer_;
};
