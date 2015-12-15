#include "mpi_process_manager.h"

#include "mpi_process.h"

mpi_process_manager& mpi_process_manager::instance(int argc, char** argv)
{
  static mpi_process_manager mgr(argc, argv);
  return mgr;
}

int mpi_process_manager::execute()
{
  boost::mpi::communicator world;
  mpi_process* process = create_mpi_process(world.rank());
  return process->execute();
}

mpi_process* mpi_process_manager::create_mpi_process(int rank)
{
  if(0 == rank)
  {
    return new main_mpi_process(argc_, argv_);
  }
  else
  {
    return new worker_mpi_process(argc_, argv_);
  }
}

mpi_process_manager::mpi_process_manager(int argc, char** argv) :
  argc_(argc),
  argv_(argv),
  env_(argc_, argv_)
{
}
