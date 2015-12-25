#include "global_settings_io.h"

#include <logging.h>
#include <utils.h>

#include <boost/filesystem.hpp>

const std::string invalid_structure = "Invalid structure of global config file.";

global_settings_io::global_settings_io()
{
}

void global_settings_io::import_settings(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
    settings_file_name_ = file_path;
  }
  catch(YAML::Exception& e)
  {
    LOG(logger::error, std::string("Failed to load global settings file from \"") + file_path + "\".\n\tError: " + e.what());
    return;
  }
  check_input_validity(node);
  settings_.set_results_dir(node[constants::results_dir].as<std::string>());
  settings_.set_generation_dir(node[constants::generation_dir].as<std::string>());
  settings_.set_excitation_file_name(node[constants::excitation_file_name].as<std::string>());
  settings_.set_relaxation_file_name(node[constants::relaxation_file_name].as<std::string>());
  settings_.set_trajectory_file_name(node[constants::trajectory_file_name].as<std::string>());
  settings_.set_eigens_file_name(node[constants::eigens_file_name].as<std::string>());
  settings_.set_nodes_file_name(node[constants::nodes_file_name].as<std::string>());
  settings_.set_dump_data(node[constants::dump_data].as<bool>());
  settings_.set_dump_step(node[constants::dump_step].as<std::size_t>());
  settings_.set_time_limit(node[constants::time_limit].as<std::size_t>());
}

void global_settings_io::export_settings(const std::string& output_dir)
{
  if(!settings_file_name_.empty())
  {
    namespace fs = boost::filesystem;
    std::string config_dir = output_dir + "/config";
    fs::path out_path(config_dir);
    fs::create_directory(out_path);
    utils::copy_file(settings_file_name_, config_dir);
  }
}

const global_settings& global_settings_io::get_settings() const
{
  return settings_;
}

void global_settings_io::check_input_validity(const YAML::Node& node)
{
  if(!node[constants::results_dir] ||
    !node[constants::generation_dir] ||
    !node[constants::excitation_file_name] ||
    !node[constants::relaxation_file_name] ||
    !node[constants::trajectory_file_name] ||
    !node[constants::eigens_file_name] ||
    !node[constants::nodes_file_name] ||
    !node[constants::dump_data] ||
    !node[constants::dump_step] ||
    !node[constants::time_limit])
  {
    throw std::runtime_error(invalid_structure);
  }
}
