#include "global_settings_importer.h"

global_settings_importer::global_settings_importer(const std::string& file_path)
{
  YAML::Node node = YAML::LoadFile(file_path);
  if(node[constants::results_dir])
  {
    settings_.set_results_dir(node[constants::results_dir].as<std::string>());
  }
  if(node[constants::trajectory_output_dir])
  {
    settings_.set_trajectory_output_dir(node[constants::trajectory_output_dir].as<std::string>());
  }
  if(node[constants::excitation_output_file])
  {
    settings_.set_excitation_output_file(node[constants::excitation_output_file].as<std::string>());
  }
  if(node[constants::relaxation_output_file])
  {
    settings_.set_relaxation_output_file(node[constants::relaxation_output_file].as<std::string>());
  }
}

const global_settings& global_settings_importer::get_settings() const
{
  return settings_;
}
