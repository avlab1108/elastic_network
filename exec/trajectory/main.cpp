#include <mpi_process_manager.h>

int main(int argc, char** argv)
{
  mpi_process_manager& m = mpi_process_manager::instance(argc, argv);
  return m.execute();
}
