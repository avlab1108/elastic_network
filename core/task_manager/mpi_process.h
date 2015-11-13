#pragma once

#include <config.h>

#include <boost/mpi.hpp>

class mpi_process
{
public:
  mpi_process(int argc, char* argv[]);
  virtual void execute() = 0;

protected:
  boost::mpi::environment env_;
  boost::mpi::communicator world_;
};

class main_mpi_process : public mpi_process
{
public:
  main_mpi_process(int argc, char* argv[]);
  virtual void execute() override;
};

class worker_mpi_process : public mpi_process
{
public:
  worker_mpi_process(int argc, char* argv[]);
  virtual void execute() override;

private:
  std::string retrieve_user_setting_path(int argc, char* argv[]);

private:
  config config_;
};
