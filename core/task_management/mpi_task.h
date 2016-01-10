#pragma once

#include "base_task.h"

#include <boost/mpi/communicator.hpp>

class mpi_task : public base_task
{
public:
  mpi_task(const std::shared_ptr<base_task>& main, const std::shared_ptr<base_task>& slave);

  void set_main_task(const std::shared_ptr<base_task>& task);
  void set_slave_task(const std::shared_ptr<base_task>& task);

  virtual int execute() override;

private:
  std::shared_ptr<base_task> main_task_;
  std::shared_ptr<base_task> slave_task_;
  boost::mpi::communicator world_;
};
