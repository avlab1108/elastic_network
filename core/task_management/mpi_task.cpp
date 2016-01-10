#include "mpi_task.h"

#include <logging.h>

#include <boost/mpi/environment.hpp>

mpi_task::mpi_task(const std::shared_ptr<base_task>& main, const std::shared_ptr<base_task>& slave) :
  main_task_(main),
  slave_task_(slave)
{
}

int mpi_task::execute()
{
  if(!boost::mpi::environment::initialized())
  {
    LOG(logger::critical, "MPI environment should be initialized before communicator usage.");
    return -1;
  }
  if(0 == world_.rank())
  {
    return main_task_ ? main_task_->execute() : 0;
  }
  else
  {
    return slave_task_ ? slave_task_->execute() : 0;
  }
}
