#pragma once

#include <config.h>
#include <command_line.h>

#include <boost/mpi.hpp>

class mpi_process
{
public:
  mpi_process(int argc, char** argv);
  ~mpi_process();
  virtual int execute() = 0;

protected:
  command_line command_line_;
  boost::mpi::communicator world_;
  config config_;
};

class main_mpi_process : public mpi_process
{
public:
  main_mpi_process(int argc, char** argv);
  virtual int execute() override;

private:
  void create_results_dir();

private:
  std::string results_dir_;
};

class worker_mpi_process : public mpi_process
{
public:
  worker_mpi_process(int argc, char** argv);
  virtual int execute() override;
};
