/**
 * @file trajectory_mpi_tasks.h
 * @brief This file contains @ref trajectory_main_task and @ref trajectory_slave_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "base_task.h"

#include <boost/mpi/communicator.hpp>

/**
 * @class trajectory_main_task
 * @brief Main MPI task for trajectory generation.
 */
class trajectory_main_task : public proxy_task
{
public:
  /**
   * @brief Constructs main task.
   */
  trajectory_main_task();
  /**
   * @brief Base interface override.
   */
  virtual void pre_execute() override;

private:
  /// World communicator.
  boost::mpi::communicator world_;
};

/**
 * @class trajectory_slave_task
 * @brief Slave (working) MPI task for trajectory generation.
 */
class trajectory_slave_task : public proxy_task
{
public:
  /**
   * @brief Constructs working task.
   */
  trajectory_slave_task();
  /**
   * @brief Base interface override.
   */
  virtual void pre_execute() override;

private:
  /// World communicator.
  boost::mpi::communicator world_;
};
