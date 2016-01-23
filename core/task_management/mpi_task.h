/**
 * @file mpi_task.h
 * @brief This file contains @ref mpi_task classes.
 * @author Minas Hovhannisyan
 */
#pragma once

#include "base_task.h"

#include <boost/mpi/communicator.hpp>

/**
 * @class mpi_task
 * @brief Defines base task for MPI-based tasks.
 *
 * MPI-based tasks consist of 2 tasks:
 * \n 1) main process task - for coodinating execution.
 * \n 2) slave process task - for performing real task.
 */
class mpi_task : public base_task
{
public:
  /**
   * @brief Constructs MPI-based task from provided tasks.
   * @param main Main task.
   * @param slave Slave task.
   */
  mpi_task(const std::shared_ptr<base_task>& main, const std::shared_ptr<base_task>& slave);

  /**
   * @brief Execute interface override.
   * @return Execution status.
   */
  virtual int execute() override;

private:
  /// Main task.
  std::shared_ptr<base_task> main_task_;
  /// Slave task.
  std::shared_ptr<base_task> slave_task_;
  /// World communicator.
  boost::mpi::communicator world_;
};
