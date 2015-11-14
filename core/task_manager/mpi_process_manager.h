#pragma once

class mpi_process;

class mpi_process_manager
{
public:
  static mpi_process_manager& instance(int argc, char** argv);

public:
  int execute();

private:
  mpi_process* create_mpi_process(int rank);

private:
  mpi_process_manager(int argc, char** argv);
  mpi_process_manager(const mpi_process_manager&) = delete;
  mpi_process_manager& operator=(const mpi_process_manager&) = delete;

private:
  int argc_;
  char** argv_;
};
