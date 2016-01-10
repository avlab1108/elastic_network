/**
 * @file mpi_application.h
 * @brief This file contains @a mpi_application class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "standalone_application.h"

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

class mpi_task;

/**
 * @class mpi_application
 * @brief Base class for MPI-based applications.
 *
 * Provides pre-execution hooks for main and slave processes to allow coordination of execution flow. This can include data transmission and synchronization.
 */
class mpi_application : public standalone_application
{
public:
  /**
   * @brief Constructs application with provided command line arguments and task for execution.
   * @param argc Argument count.
   * @param argv Argument values.
   * @param task Task for execution.
   */
  mpi_application(int argc, char** argv, const std::shared_ptr<mpi_task>& task);

private:
  /**
   * @brief Hook for pre-execution of task.
   *
   * Delegates real actions to @ref pre_execute_main_process or @ref pre_execute_slave_process according to process rank.
   */
  virtual void pre_execute() override;

  /**
   * @brief Hook for pre-execution of main process.
   */
  virtual void pre_execute_main_process();
  /**
   * @brief Hook for post-execution of main process.
   */
  virtual void pre_execute_slave_process();

private:
  /// MPI environment.
  boost::mpi::environment env_;
  /// World communicator.
  boost::mpi::communicator world_;
};
