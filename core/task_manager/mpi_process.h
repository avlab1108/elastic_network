#pragma once

#include <config.h>

#include <boost/mpi.hpp>

class command_line
{
public:
  command_line(int argc, char** argv);
  std::string get_user_settings_path() const;
  std::string get_global_settings_path() const;

private:
  std::string user_settings_path_;
  std::string global_settings_path_;
};

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
