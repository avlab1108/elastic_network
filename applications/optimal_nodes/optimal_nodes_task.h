/**
 * @file optimal_nodes_task.h
 * @brief This file contains @a optimal_nodes_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <base_task.h>

/**
 * @class optimal_nodes_task
 * @brief Calculates optimal nodes for trajectory generation process.
 */
class optimal_nodes_task : public base_task
{
public:
  /**
   * @brief Base interface override.
   * @return Execution status.
   */
  virtual int execute() override;
};
