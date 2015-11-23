#include "trajectory_task.h"

#include <excitor.h>
#include <relaxer.h>
#include <result_observer.h>
#include <node_chooser.h>
#include <logging.h>

#include <boost/filesystem.hpp>

trajectory_process::trajectory_process(const std::string& results_dir, const std::size_t run_id, const config& conf) :
  results_dir_(results_dir),
  run_id_(run_id),
  config_(conf)
{
}

void trajectory_process::prepare_output_directory()
{
  const global_settings& gs = config_.get_global_settings();
  const std::string& out_dir = results_dir_ + "/" + gs.get_generation_dir() + "_" + std::to_string(run_id_); 
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

void trajectory_process::execute()
{
  prepare_output_directory();
  const global_settings& gs = config_.get_global_settings();
  const std::string& output_file = generation_dir_ + "/" + gs.get_excitation_file_name();
  std::ofstream fout(output_file);
  if(!fout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
    return;
  }
  const user_settings& sets = config_.get_user_settings();
  network net = sets.get_network();
  network::node_positions_type initial_state = net.get_node_positions();

  std::shared_ptr<result_observer> obs(new stream_dumper(stream_dumper::format_type::raw, fout));
  LOG(logger::info, std::string("Started execution for id \"") + std::to_string(run_id_) + "\" with following parameters:\n \
      \ttime step: " + std::to_string(sets.get_time_step()) + ", \n\
      \texcitation time: " + std::to_string(sets.get_excitation_time()) + ", \n\
      \tforce summary module: " + std::to_string(sets.get_fs()));
  excitor x(net, initial_state, sets.get_time_step(), sets.get_excitation_time(), sets.get_fs()); 
  x.set_result_observer(obs);
  std::clock_t begin = clock();
  x.run();

  const std::string& relaxation_output_file = generation_dir_ + "/" + gs.get_relaxation_file_name();
  std::ofstream rout(relaxation_output_file);
  if(!rout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + relaxation_output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
    return;
  }
  const std::string& trajectory_output_file = generation_dir_ + "/" + gs.get_trajectory_file_name();
  std::ofstream tout(trajectory_output_file);
  if(!tout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + trajectory_output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
    return;
  }
  node_chooser chooser(sets.get_network());
  const node_chooser::node_numbers_type& nodes = chooser.choose();
  std::shared_ptr<trajectory_dumper> traj_dumper(new trajectory_dumper(tout, initial_state, nodes, gs.get_dump_step()));
  std::shared_ptr<result_observer> robs(new stream_dumper(stream_dumper::format_type::raw, rout));
  std::shared_ptr<composite_result_observer> comp(new composite_result_observer());
  std::shared_ptr<stability_checker> stab_checker(new stability_checker(initial_state, nodes));
  comp->add_result_observer(robs);
  comp->add_result_observer(traj_dumper);
  comp->add_result_observer(stab_checker);
  relaxer r(net, initial_state, sets.get_time_step(), sets.get_time_limit());
  r.set_result_observer(comp);
  r.run();

  std::clock_t end = clock();
  LOG(logger::info, std::string("Finished execution for id \"") + std::to_string(run_id_) + "\". Elapsed CPU time: " + std::to_string(static_cast<double>(end-begin)/CLOCKS_PER_SEC) + " seconds.");
}

trajectory_task::trajectory_task(const std::string& results_dir, const std::vector<std::size_t>& run_ids, const config& conf)
{
  for(std::size_t i = 0; i < run_ids.size(); ++i)
  {
    add_process(std::make_shared<trajectory_process>(results_dir, run_ids[i], conf));
  }
}
