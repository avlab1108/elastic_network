/**
 * @file relaxer.h
 * @brief This file contains @a relaxer class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <trajectory_worker.h>
#include <network.h>
#include <common_types.h>

/**
 * @class relaxer
 * @brief Simulates relaxation process of network with provided parameters.
 */
class relaxer : public trajectory_worker
{
public:
  /**
   * @brief Constructs relaxer for provided network and parameters.
   * @param net Network.
   * @param initial_positions Initial positions of network nodes.
   * @param step Integration step.
   * @param max_time Integration upper limit.
   */
  relaxer(network& net, const node_positions_type& initial_positions, const double step, const std::size_t max_time);

  /**
   * @brief Implementation of base class interface.
   *        Performs simulation process.
   */
  virtual void run() override;

private:
  /// Integration step.
  const double step_;
  /// Integration upper limit.
  const std::size_t max_time_;
};
