#include "global_settings.h"

global_settings::global_settings() :
  results_dir_(), //TODO: add hardcoded default values
  generation_dir_(),
  excitation_file_name_(),
  relaxation_file_name_()
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
