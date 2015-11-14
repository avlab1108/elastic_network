#include "trajectory_task.h"

#include <excitor.h>
#include <result_observer.h>
#include <logging.h>

#include <boost/filesystem.hpp>

trajectory_process::trajectory_process(const std::size_t run_id, const config& conf) :
  run_id_(run_id),
  config_(conf)
{
}

void trajectory_process::execute()
{
  //prepare_output_directory();
  const std::string output_file;
  const global_settings& gs = config_.get_global_settings();
  boost::filesystem::path dir(gs.get_results_dir());
  if(!boost::filesystem::create_directory(dir))
  {
    LOG(logger::error, "Failed to create output directory for results.");
  }
  std::ofstream fout(gs.get_results_dir() + "/" + gs.get_excitation_output_file() + "_" + std::to_string(run_id_));
  if(!fout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
    return;
  }
  const user_settings& sets = config_.get_user_settings();
  network net = sets.get_network();
  network::node_positions_type state = net.get_node_positions();
  std::shared_ptr<result_observer> obs(new stream_dumper(stream_dumper::format_type::raw, &fout));
  LOG(logger::info, std::string("Started execution for id \"") + std::to_string(run_id_) + "\" with following parameters:\n \
      \ttime step: " + std::to_string(sets.get_time_step()) + ", \n\
      \texcitation time: " + std::to_string(sets.get_excitation_time()) + ", \n\
      \tforce summary module: " + std::to_string(sets.get_fs()));
  excitor x(net, state, sets.get_time_step(), sets.get_excitation_time(), sets.get_fs()); 
  x.set_result_observer(obs);
  std::clock_t begin = clock();
  x.run();
  std::clock_t end = clock();
  LOG(logger::info, std::string("Finished execution for id \"") + std::to_string(run_id_) + "\". Elapsed CPU time: " + std::to_string(static_cast<double>(end-begin)/CLOCKS_PER_SEC) + " seconds.");
}

trajectory_task::trajectory_task(const config& config, const std::vector<std::size_t>& run_ids) :
  config_(config),
  run_ids_(run_ids)
{
  for(std::size_t i = 0; i < run_ids_.size(); ++i)
  {
    add_process(std::make_shared<trajectory_process>(run_ids_[i], config_));
  }
}
