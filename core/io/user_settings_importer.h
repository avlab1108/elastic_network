#pragma once

#include <network.h>
#include <user_settings.h>
#include <yaml-cpp/yaml.h>

namespace constants
{
const std::string fs = "Fs";
const std::string network_file_path = "networkFile";
const std::string l0 = "L0";
const std::string nodes = "nodes";
const std::string links = "links";
const std::string time_step = "timeStep";
const std::string time_limit = "timeLimit";
const std::string excitation_time = "timeIni";
const std::string simulations_count = "runNum";
const std::string force_application_nodes = "activeNodes";
const std::string visualization_nodes = "visualizationNodes";
}

namespace YAML
{
class Node;
}

class user_settings_importer
{
public:
  user_settings_importer(const std::string& file_path);
  const user_settings& get_settings() const;
  
private:
  void import_network_from_external_file(const std::string& file_path);
  network read_network_from_yaml(const YAML::Node& node);
  network read_network_from_yaml_file(const std::string& file_path);
  network read_network_from_csv_file(const std::string& file_path);

private:
  user_settings settings_;
};
