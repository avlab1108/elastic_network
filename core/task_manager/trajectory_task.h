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
  void prepare_output_directory();
  void pre_excitement();
  void post_excitement();
  void pre_relaxation();
  void post_relaxation();

private:
  std::string generation_dir_;
  const std::size_t run_id_;
  config config_;
};

class trajectory_task : public task
{
public:
  trajectory_task(const std::vector<std::size_t>& run_ids, const config& conf);
};
