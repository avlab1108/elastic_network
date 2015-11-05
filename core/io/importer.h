#pragma once

#include <network.h>
#include <settings.h>
#include <yaml-cpp/yaml.h>

namespace constants
{
const std::string fs = "Fs";
const std::string networkFilePath = "graphFile";
const std::string l0 = "L0";
const std::string nodes = "nodes";
const std::string links = "links";
const std::string timeLimit = "timeLimit";
const std::string excitementTime = "timeIni";
const std::string forceApplicationNodes = "activeNodes";
const std::string visualizationNodes = "visualizationNodes";
}

namespace YAML
{
class Node;
}

class importer
{
public:
  importer(const std::string& file_path);

  const settings& get_settings() const;
  
private:
  void read_network_from_yaml(const YAML::Node& node);
  void import_network_from_external_file(const std::string& file_path);
  void import_network_from_yaml_file(const std::string& file_path);
  void import_network_from_csv_file(const std::string& file_path);

private:
  settings settings_;
};
