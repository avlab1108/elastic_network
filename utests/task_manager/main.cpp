#include <mpi_process_manager.h>
#include <trajectory_task.h>
#include <utils.h>

#include <cstdlib>
#include <memory>

int main(int argc, char** argv)
{
  //config c("./config.yaml");
  //trajectory_process task1(12, c);
  //task1.execute();

  mpi_process_manager& m = mpi_process_manager::instance(argc, argv);
  return m.execute();
}
