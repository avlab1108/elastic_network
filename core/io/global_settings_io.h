#pragma once

#include <global_settings.h>
#include <yaml-cpp/yaml.h>

namespace constants
{
const std::string results_dir = "resultsDir";
const std::string generation_dir = "generationDir";
const std::string excitation_file_name = "excitationFileName";
const std::string relaxation_file_name = "relaxationFileName";
const std::string trajectory_file_name = "trajectoryFileName";
const std::string eigens_file_name = "eigensFileName";
const std::string nodes_file_name = "nodesFileName";
const std::string dump_data = "dumpData";
const std::string dump_step = "dumpStep";
const std::string time_limit = "timeLimit";
const std::string forces_dynamic = "forcesDynamic";
}

namespace YAML
{
class Node;
}

class global_settings_io
{
public:
  global_settings_io();

  void import_settings(const std::string& file_path);
  void export_settings(const std::string& output_dir);

  const global_settings& get_settings() const;
  void check_input_validity(const YAML::Node& node);

private:
  global_settings settings_;
  std::string settings_file_name_;
};
