#include "relaxer_mpi_tasks.h"
#include "relaxer_task.h"

#include <config.h>
#include <utils.h>
#include <node_chooser.h>

#include <boost/mpi/nonblocking.hpp>
#include <boost/serialization/vector.hpp>

#include <memory>

relaxer_main_task::relaxer_main_task()
{
}

void relaxer_main_task::pre_execute()
{
  world_.barrier();
  user_settings& us = get_config()->get_user_settings();
  const std::size_t sim_num = us.get_simulations_count();
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
  if(us.get_visualization_nodes().empty())
  {
		network initial(us.get_network());
		//TODO need to check optional
		initial.get_node_positions() = us.get_equilibrium_state_spec()->positions;
    us.set_visualization_nodes(node_chooser(initial).choose());
  }
  if(0 != remainder)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < remainder; ++j)
    {
      sim_nums.push_back(current++);
    }
    assign_task(std::make_shared<group_relaxer_task>(sim_nums));
  }
}

relaxer_slave_task::relaxer_slave_task()
{
}

void relaxer_slave_task::pre_execute()
{
  world_.barrier();
  std::vector<std::size_t> sim_nums;
  world_.recv(0, 1, sim_nums);
  assign_task(std::make_shared<group_relaxer_task>(sim_nums));
}
