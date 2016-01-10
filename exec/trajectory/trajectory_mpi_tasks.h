#pragma once

#include "base_task.h"

#include <boost/mpi/communicator.hpp>

class trajectory_main_task : public proxy_task
{
public:
  trajectory_main_task();
  virtual void pre_execute() override;

private:
  boost::mpi::communicator world_;
};

class trajectory_slave_task : public proxy_task
{
public:
  trajectory_slave_task();
  virtual void pre_execute() override;

private:
  boost::mpi::communicator world_;
};
