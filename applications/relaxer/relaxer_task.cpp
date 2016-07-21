#include "relaxer_task.h"

#include <common_types.h>
#include <config.h>
#include <excitor.h>
#include <logging.h>
#include <node_chooser.h>
#include <relaxer.h>
#include <result_observer.h>
#include <core_application.h>

#include <boost/filesystem.hpp>

relaxer_task::relaxer_task(const std::size_t run_id) :
  run_id_(run_id)
{
}

void relaxer_task::prepare_output_directory()
{
  const global_settings& gs = get_config()->get_global_settings();
  const std::string& out_dir = core_application::instance()->get_work_directory() + "/" + gs.get_generation_dir() + "_" + std::to_string(run_id_); 
  boost::filesystem::path dir(out_dir);
  if(boost::filesystem::is_directory(dir))
  {
    LOG(logger::info, std::string("Output directory \"") + out_dir + "\" already exists. Trying to use it.");
  }
  else if(!boost::filesystem::create_directory(dir))
  {
    LOG(logger::error, "Failed to create output directory for results.");
  }
  generation_dir_ = out_dir;
}

int relaxer_task::execute()
{
  prepare_output_directory();
  const global_settings& gs = get_config()->get_global_settings();
  const user_settings& us = get_config()->get_user_settings();
  network net = us.get_network();
	if(!us.get_equilibrium_state_spec())
	{
    LOG(logger::error, "Equilibrium state of network is not provided.");
    return -1;
	}
  const equilibrium_state_spec& equilibrium_state = *us.get_equilibrium_state_spec();

  LOG(logger::info, std::string("Started execution for id \"") + std::to_string(run_id_) + "\" with following parameters:\n \
      \ttime step: " + std::to_string(us.get_excitation_time_step()) + ", \n\
      \texcitation time: " + std::to_string(us.get_excitation_time()) + ", \n\
      \tforce summary module: " + std::to_string(us.get_fs()));
  
  const std::string& relaxer_output_file = generation_dir_ + "/" + gs.get_trajectory_file_name();
  std::ofstream tout(relaxer_output_file);
  if(!tout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + relaxer_output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
    return -1;
  }
  const node_positions_t& current_state = net.get_node_positions();
  const node_chooser::node_numbers_type& nodes = us.get_visualization_nodes();
  //TODO MH: check for valid indexes
  std::shared_ptr<trajectory_dumper> traj_dumper(new trajectory_dumper(tout, equilibrium_state, nodes, gs.get_dump_step()));
  std::shared_ptr<composite_result_observer> comp(new composite_result_observer());
  std::shared_ptr<stability_checker> stab_checker(new stability_checker(equilibrium_state, current_state, nodes, gs.get_stabilization_spec()));
  if(gs.get_dump_data())
  {
    const std::string& relaxation_output_file = generation_dir_ + "/" + gs.get_relaxation_file_name();
    std::shared_ptr<result_observer> robs(new file_dumper(relaxation_output_file));
    comp->add_result_observer(robs);
  }

  std::clock_t begin = clock();

  comp->add_result_observer(traj_dumper);
  comp->add_result_observer(stab_checker);
  relaxer r(net, equilibrium_state, us.get_relaxation_time_step_spec(), gs.get_relaxation_time_limit());
  r.set_result_observer(comp);
  r.run();

  std::clock_t end = clock();
  LOG(logger::info, std::string("Finished execution for id \"") + std::to_string(run_id_) + "\". Elapsed CPU time: " + std::to_string(static_cast<double>(end-begin)/CLOCKS_PER_SEC) + " seconds.");
  return 0;
}

group_relaxer_task::group_relaxer_task(const std::vector<std::size_t>& run_ids)
{
  for(std::size_t i = 0; i < run_ids.size(); ++i)
  {
    add_task(std::make_shared<relaxer_task>(run_ids[i]));
  }
}
