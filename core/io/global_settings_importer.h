#pragma once

#include <global_settings.h>
#include <yaml-cpp/yaml.h>

namespace constants
{
const std::string results_dir = "resultsDirPattern";
const std::string trajectory_output_dir = "trajectoryDirPattern";
const std::string excitation_output_file = "excitationFileNamePattern";
const std::string relaxation_output_file = "relaxationFileNamePattern";
}

namespace YAML
{
class Node;
}

class global_settings_importer
{
public:
  global_settings_importer(const std::string& file_path);
  const global_settings& get_settings() const;

private:
  global_settings settings_;
};
