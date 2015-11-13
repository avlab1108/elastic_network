#include "global_settings.h"

global_settings::global_settings() :
  results_dir_(), //TODO: add hardcoded default values
  trajectory_output_dir_(),
  excitation_output_dir_(),
  relaxation_output_dir_()
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

void global_settings::set_trajectory_output_dir(const std::string& dir)
{
  trajectory_output_dir_ = dir;
}

const std::string& global_settings::get_trajectory_output_directory() const
{
  return trajectory_output_dir_;
}

void global_settings::set_excitation_output_file(const std::string& dir)
{
  excitation_output_dir_ = dir;
}

const std::string& global_settings::get_excitation_output_file() const
{
  return excitation_output_dir_;
}

void global_settings::set_relaxation_output_file(const std::string& dir)
{
  relaxation_output_dir_ = dir;
}

const std::string& global_settings::get_relaxation_output_file() const
{
  return relaxation_output_dir_;
}
