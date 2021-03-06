/**
 * @file optimal_nodes_task.h
 * @brief This file contains @ref optimal_nodes_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <base_task.h>

#include <string>
#include <vector>

class config;

/**
 * @class trajectory_task
 * @brief Generates single trajectory associated with provided id.
 */
class trajectory_task : public base_task
{
public:
  /**
   * @brief Constructs task with associated id.
   * @param run_id Task id.
   */
  trajectory_task(const std::size_t run_id);
  /**
   * @brief Base interface override.
   * @return Execution status.
   */
  virtual int execute() override;

private:
  /**
   * @brief Prepares output directory for trajectory.
   */
  void prepare_output_directory();
  /**
   * @brief Hook for pre-excitement.
   */
  void pre_excitement();
  /**
   * @brief Hook for post-excitement.
   */
  void post_excitement();
  /**
   * @brief Hook for pre-relaxation.
   */
  void pre_relaxation();
  /**
   * @brief Hook for post-relaxation.
   */
  void post_relaxation();

private:
  /// Output directory name.
  std::string generation_dir_;
  /// Task id.
  const std::size_t run_id_;
};

/**
 * @class group_trajectory_task
 * @brief Group task for generating multiple trajectories.
 */
class group_trajectory_task : public complex_task
{
public:
  /**
   * @brief Constructs group task for specified ids.
   */
  group_trajectory_task(const std::vector<std::size_t>& run_ids);
};
