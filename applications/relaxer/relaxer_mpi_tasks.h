/**
 * @file relaxer_mpi_tasks.h
 * @brief This file contains @ref relaxer_main_task and @ref relaxer_slave_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "base_task.h"

#include <boost/mpi/communicator.hpp>

/**
 * @class relaxer_main_task
 * @brief Main MPI task for relaxer generation.
 */
class relaxer_main_task : public proxy_task
{
public:
  /**
   * @brief Constructs main task.
   */
  relaxer_main_task();
  /**
   * @brief Base interface override.
   */
  virtual void pre_execute() override;

private:
  /// World communicator.
  boost::mpi::communicator world_;
};

/**
 * @class relaxer_slave_task
 * @brief Slave (working) MPI task for relaxer generation.
 */
class relaxer_slave_task : public proxy_task
{
public:
  /**
   * @brief Constructs working task.
   */
  relaxer_slave_task();
  /**
   * @brief Base interface override.
   */
  virtual void pre_execute() override;

private:
  /// World communicator.
  boost::mpi::communicator world_;
};
