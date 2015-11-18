#pragma once

#include "task.h"
#include <config.h>

#include <string>
#include <vector>

class trajectory_process : public process
{
public:
  trajectory_process(const std::string& results_dir, const std::size_t run_id, const config& conf);
  virtual void execute() override;

private:
  void prepare_output_directory();

private:
  const std::string results_dir_;
  std::string generation_dir_;
  const std::size_t run_id_;
  config config_;
};

class trajectory_task : public task
{
public:
  trajectory_task(const std::string& results_dir, const std::vector<std::size_t>& run_ids, const config& conf);
};
