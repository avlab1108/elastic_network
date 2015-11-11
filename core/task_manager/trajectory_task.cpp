#include "trajectory_task.h"

#include <excitor.h>
#include <result_observer.h>
#include <logging.h>

trajectory_process::trajectory_process(const std::size_t run_id, const settings& config) :
  run_id_(run_id),
  config_(config)
{
}

void trajectory_process::execute()
{
  //prepare_output_directory();
  const std::string output_file;
  std::ofstream fout(output_file);
  if(!fout.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + output_file + "\". Silently stopping execution for id \"" + std::to_string(run_id_) + "\".");
  }
  network net = config_.network_();
  network::node_positions_type state = net.node_positions();
  std::shared_ptr<result_observer> obs(new stream_dumper(stream_dumper::format_type::raw, &fout));
  excitor x(net, state, 0.02, config_.excitation_time(), config_.fs()); 
}

trajectory_task::trajectory_task(const std::string& user_config_path, const std::vector<std::size_t>& run_ids) :
  user_config_path_(user_config_path),
  run_ids_(run_ids)
{
  //load_default_settings();
  load_user_config(user_config_path_);
  for(std::size_t i = 0; i < run_ids_.size(); ++i)
  {
    add_process(std::make_shared<trajectory_process>(run_ids_[i], config_));
  }
}

void trajectory_task::load_user_config(const std::string& file_name)
{
}
