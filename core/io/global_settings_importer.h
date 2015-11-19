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
const std::string dump_step = "dumpStep";
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
