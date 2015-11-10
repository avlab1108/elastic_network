#pragma once

#include "task.h"
#include <settings.h>

#include <string>
#include <vector>

class trajectory_process : public process
{
public:
  trajectory_process(const std::size_t run_id, const settings& config);
  virtual void execute() override;

private:
  const std::size_t run_id_;
  settings config_;
};

class trajectory_task : public task
{
public:
  trajectory_task(const std::string& user_config_path, const std::vector<std::size_t>& run_ids);

private:
  void load_user_config(const std::string& user_config_path);

private:
  const std::string user_config_path_;
  const std::vector<std::size_t> run_ids_;
  settings config_;
};
