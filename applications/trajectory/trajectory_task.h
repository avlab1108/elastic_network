#pragma once

#include "base_task.h"

#include <string>
#include <vector>

class config;

class trajectory_task : public base_task
{
public:
  trajectory_task(const std::size_t run_id);
  virtual int execute() override;

private:
  void prepare_output_directory();
  void pre_excitement();
  void post_excitement();
  void pre_relaxation();
  void post_relaxation();

private:
  std::string generation_dir_;
  const std::size_t run_id_;
};

class group_trajectory_task : public complex_task
{
public:
  group_trajectory_task(const std::vector<std::size_t>& run_ids);
};
