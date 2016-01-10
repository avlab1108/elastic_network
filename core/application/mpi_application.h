#pragma once

#include "standalone_application.h"

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>

class mpi_task;

class mpi_application : public standalone_application
{
public:
  mpi_application(int argc, char** argv, const std::shared_ptr<mpi_task>& task);

private:
  virtual void pre_execute() override;

  virtual void pre_execute_main_process();
  virtual void pre_execute_slave_process();

private:
  boost::mpi::environment env_;
  boost::mpi::communicator world_;
};
