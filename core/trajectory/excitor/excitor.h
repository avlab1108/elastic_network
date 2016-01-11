/**
 * @file excitor.h
 * @brief This file contains @a excitor class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <trajectory_worker.h>
#include <common_types.h>

/**
 * @class excitor
 * @brief Simulates excitation process of network with provided parameters.
 *
 * Simulation is performed by numeric integration of network dynamics. Here is appropriate ODE:
 * Here goes ODE.
 */
class excitor : public trajectory_worker
{
public:
  /**
   * @brief Constructs excitor for provided network and parameters.
   * @param net Network.
   * @param initial_positions Initial positions of network nodes.
   * @param step Integration step.
   * @param time Integration upper limit.
   * @param fspec Force specialization.
   */
  excitor(network& net, const node_positions_type& initial_positions, const double step, const std::size_t time, const forces_spec& fspec);

  /**
   * @brief Implementation of base class interface.
   *        Performs simulation process.
   */
  virtual void run() override;

private:
  /// Integration step.
  const double step_;
  /// Integration upper limit.
  const std::size_t time_;
};
