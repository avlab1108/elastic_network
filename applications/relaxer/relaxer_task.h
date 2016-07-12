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
 * @class relaxer_task
 * @brief Generates single relaxer associated with provided id.
 */
class relaxer_task : public base_task
{
public:
  /**
   * @brief Constructs task with associated id.
   * @param run_id Task id.
   */
  relaxer_task(const std::size_t run_id);
  /**
   * @brief Base interface override.
   * @return Execution status.
   */
  virtual int execute() override;

private:
  /**
   * @brief Prepares output directory for relaxer.
   */
  void prepare_output_directory();

private:
  /// Output directory name.
  std::string generation_dir_;
  /// Task id.
  const std::size_t run_id_;
};

/**
 * @class group_relaxer_task
 * @brief Group task for generating multiple trajectories.
 */
class group_relaxer_task : public complex_task
{
public:
  /**
   * @brief Constructs group task for specified ids.
   */
  group_relaxer_task(const std::vector<std::size_t>& run_ids);
};
