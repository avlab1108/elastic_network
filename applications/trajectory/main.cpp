#include "trajectory_mpi_tasks.h"

#include <mpi_application.h>
#include <mpi_task.h>

int main(int argc, char** argv)
{
  auto task = std::make_shared<mpi_task>(std::make_shared<trajectory_main_task>(), std::make_shared<trajectory_slave_task>());
  mpi_application app(argc, argv, task);
  return app.execute();
}
