#include "global_settings_importer.h"

#include <logging.h>

global_settings_importer::global_settings_importer(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    LOG(logger::error, std::string("Failed to load global settings file from \"") + file_path + "\".\n\tError: " + e.what());
    return;
  }
  if(node[constants::results_dir])
  {
    settings_.set_results_dir(node[constants::results_dir].as<std::string>());
  }
  if(node[constants::generation_dir])
  {
    settings_.set_generation_dir(node[constants::generation_dir].as<std::string>());
  }
  if(node[constants::excitation_file_name])
  {
    settings_.set_excitation_file_name(node[constants::excitation_file_name].as<std::string>());
  }
  if(node[constants::relaxation_file_name])
  {
    settings_.set_relaxation_file_name(node[constants::relaxation_file_name].as<std::string>());
  }
  if(node[constants::trajectory_file_name])
  {
    settings_.set_trajectory_file_name(node[constants::trajectory_file_name].as<std::string>());
  }
  if(node[constants::eigens_file_name])
  {
    settings_.set_eigens_file_name(node[constants::eigens_file_name].as<std::string>());
  }
  if(node[constants::nodes_file_name])
  {
    settings_.set_nodes_file_name(node[constants::nodes_file_name].as<std::string>());
  }
  if(node[constants::dump_step])
  {
    settings_.set_dump_step(node[constants::dump_step].as<std::size_t>());
  }
}

const global_settings& global_settings_importer::get_settings() const
{
  return settings_;
}
