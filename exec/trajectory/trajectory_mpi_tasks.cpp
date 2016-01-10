#include "trajectory_mpi_tasks.h"
#include "trajectory_task.h"

#include <config.h>
#include <utils.h>

#include <boost/mpi/nonblocking.hpp>
#include <boost/serialization/vector.hpp>

#include <memory>

trajectory_main_task::trajectory_main_task()
{
}

void trajectory_main_task::pre_execute()
{
  world_.barrier();
  const std::size_t sim_num = get_config()->get_user_settings().get_simulations_count();
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
    assign_task(std::make_shared<group_trajectory_task>(sim_nums));
  }
}

trajectory_slave_task::trajectory_slave_task()
{
}

void trajectory_slave_task::pre_execute()
{
  world_.barrier();
  std::vector<std::size_t> sim_nums;
  world_.recv(0, 1, sim_nums);
  assign_task(std::make_shared<group_trajectory_task>(sim_nums));
}
