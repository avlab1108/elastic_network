#include "trajectory_task.h"

trajectory_process::trajectory_process(const std::size_t run_id, const settings& config) :
  run_id_(run_id),
  config_(config)
{
}

void trajectory_process::execute()
{
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
