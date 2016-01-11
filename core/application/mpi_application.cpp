#include "mpi_application.h"

#include <mpi_task.h>
#include <config.h>

mpi_application::mpi_application(int argc, char** argv, const std::shared_ptr<mpi_task>& task) :
  standalone_application(argc, argv, task),
  env_(argc, argv)
{
  instance_ = this;
}

void mpi_application::pre_execute()
{
 if(0 == world_.rank())
 {
   prepare_work_directory();
   pre_execute_main_process();
 }
 else
 {
   pre_execute_slave_process();
 }
}

void mpi_application::pre_execute_main_process()
{
  for(int i = 1; i < world_.size(); ++i)
  {
    world_.send(i, 0, timestamp_);
  }
}

void mpi_application::pre_execute_slave_process()
{
  world_.recv(0, 0, timestamp_);
}

void mpi_application::post_execute()
{
  if(0 == world_.rank())
  {
    get_config()->dump(get_work_directory());
  }
}
