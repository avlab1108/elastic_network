#include "mpi_process.h"
#include "trajectory_task.h"

#include <logging.h>

#include <boost/mpi/nonblocking.hpp>
#include <boost/filesystem.hpp>

#include <chrono>
#include <ctime>

mpi_process::mpi_process(int argc, char** argv) :
  command_line_(argc, argv),
  config_(command_line_.get_user_settings_path(), command_line_.get_global_settings_path())
{
}

mpi_process::~mpi_process()
{
}

main_mpi_process::main_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int main_mpi_process::execute()
{
  world_.barrier();
  using std::chrono::system_clock;
  config_.set_timestamp(system_clock::to_time_t(system_clock::now()));
  utils::create_directory(config_.get_work_directory());
  const std::size_t sim_num = config_.get_user_settings().get_simulations_count();
  const int mpi_size = world_.size() - 1;
  int single_task_size = sim_num/(0 == mpi_size ? 1 : mpi_size);
  int remainder = sim_num - single_task_size * mpi_size;
  int current = 0;
  std::vector<boost::mpi::request> requests;
  for(int i = 1; i < mpi_size + 1; ++i)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < single_task_size; ++j)
    {
      sim_nums.push_back(current++);
    }
    requests.push_back(world_.isend(i, 0, config_.get_timestamp()));
    requests.push_back(world_.isend(i, 1, sim_nums));
  }
  boost::mpi::wait_all(requests.begin(), requests.end());
  if(0 != remainder)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < remainder; ++j)
    {
      sim_nums.push_back(current++);
    }
    trajectory_task t(sim_nums, config_);
    t.run();
  }
  return 0;
}

worker_mpi_process::worker_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int worker_mpi_process::execute()
{
  world_.barrier();
  std::time_t timestamp;
  world_.recv(0, 0, timestamp);
  std::vector<std::size_t> sim_nums;
  world_.recv(0, 1, sim_nums);
  config_.set_timestamp(timestamp);
  trajectory_task t(sim_nums, config_);
  t.run();
  return 0;
}
