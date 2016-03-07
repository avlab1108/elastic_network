#include "global_settings.h"

global_settings::global_settings() :
  results_dir_("results"),
  generation_dir_("generation"),
  excitation_file_name_("excitation.txt"),
  relaxation_file_name_("relaxation.txt"),
  trajectory_file_name_("trajectory.txt"),
  eigens_file_name_("eigens.txt"),
  nodes_file_name_("nodes.txt"),
  dump_data_(true),
  dump_step_(1)
{
}

void global_settings::set_results_dir(const std::string& dir)
{
  results_dir_ = dir;
}

const std::string& global_settings::get_results_dir() const
{
  return results_dir_;
}

void global_settings::set_generation_dir(const std::string& dir)
{
  generation_dir_ = dir;
}

const std::string& global_settings::get_generation_dir() const
{
  return generation_dir_;
}

void global_settings::set_excitation_file_name(const std::string& file_name)
{
  excitation_file_name_ = file_name;
}

const std::string& global_settings::get_excitation_file_name() const
{
  return excitation_file_name_;
}

void global_settings::set_relaxation_file_name(const std::string& file_name)
{
  relaxation_file_name_ = file_name;
}

const std::string& global_settings::get_relaxation_file_name() const
{
  return relaxation_file_name_;
}

void global_settings::set_trajectory_file_name(const std::string& file_name)
{
  trajectory_file_name_ = file_name;
}

const std::string& global_settings::get_trajectory_file_name() const
{
  return trajectory_file_name_;
}

void global_settings::set_eigens_file_name(const std::string& file_name)
{
  eigens_file_name_ = file_name;
}

const std::string& global_settings::get_eigens_file_name() const
{
  return eigens_file_name_;
}

void global_settings::set_nodes_file_name(const std::string& file_name)
{
  nodes_file_name_ = file_name;
}

const std::string& global_settings::get_nodes_file_name() const
{
  return nodes_file_name_;
}

void global_settings::set_dump_data(const bool dump)
{
  dump_data_ = dump;
}

bool global_settings::get_dump_data() const
{
  return dump_data_;
}

void global_settings::set_dump_step(const std::size_t step)
{
  dump_step_ = step;
}

std::size_t global_settings::get_dump_step() const
{
  return dump_step_;
}

void global_settings::set_relaxation_time_limit(const std::size_t limit)
{
  relaxation_time_limit_ = limit;
}

std::size_t global_settings::get_relaxation_time_limit() const
{
  return relaxation_time_limit_;
}

void global_settings::set_stabilization_spec(const stabilization_spec& spec)
{
  stabilization_spec_ = spec;
}

const stabilization_spec& global_settings::get_stabilization_spec() const
{
  return stabilization_spec_;
}
