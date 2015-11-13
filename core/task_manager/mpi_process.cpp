#include "mpi_process.h"

mpi_process::mpi_process(int argc, char* argv[]) :
  env_(argc, argv)
{
}

main_mpi_process::main_mpi_process(int argc, char* argv[]) :
  mpi_process(argc, argv)
{
}

void main_mpi_process::execute()
{
}

worker_mpi_process::worker_mpi_process(int argc, char* argv[]) :
  mpi_process(argc, argv),
  config_(retrieve_user_setting_path(argc, argv))
{
}

void worker_mpi_process::execute()
{
}

std::string worker_mpi_process::retrieve_user_setting_path(int argc, char* argv[])
{
  //TODO return from command line arguments
  return "./config.yaml";
}
