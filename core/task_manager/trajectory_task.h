#pragma once

#include "task.h"
#include <config.h>

#include <string>
#include <vector>

class trajectory_process : public process
{
public:
  trajectory_process(const std::size_t run_id, const config& conf);
  virtual void execute() override;

private:
  const std::size_t run_id_;
  config config_;
};

class trajectory_task : public task
{
public:
  trajectory_task(const std::string& user_config_path, const std::vector<std::size_t>& run_ids);

private:
  const std::vector<std::size_t> run_ids_;
  config config_;
};
