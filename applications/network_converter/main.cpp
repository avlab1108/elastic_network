#include <yaml-cpp/yaml.h>

#include <boost/algorithm/string.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <utils.h>

/// Error strings.
const std::string invalid_usage       = "Invalid usage: <program name> input_network l0 output_network.";
const std::string invalid_file_type   = "Invalid file type provided.";
const std::string invalid_format      = "Invalid format of network file.";
const std::string invalid_output_file = "Cannot cannot create/open output file.";
const std::string failed_to_load      = "Failed to load network YAML file.";

/// Output YAML file keys.
const std::string nodes_key = "nodes";
const std::string links_key = "links";

node_positions_t read_nodes_from_yaml(const std::string& file_path)
{
  node_positions_t nodes;
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    std::cerr << failed_to_load << std::endl;
    return nodes;
  }
  const YAML::Node& node_positions = node[nodes_key];
  const std::size_t size = node_positions.size();
  for(std::size_t i = 0; i < size; ++i)
  {
    const point_type& position = node_positions[i].as<point_type>();
    nodes.push_back(position);
  }
  return nodes;
}

node_positions_t read_nodes_from_csv(const std::string& file_path)
{
  node_positions_t nodes;
  std::ifstream csv(file_path);
  if(!csv.is_open())
  {
    std::cerr << invalid_file_type << std::endl;
    return nodes;
  }
  std::string line;
  while(std::getline(csv, line))
  {
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" \t"), boost::token_compress_on);
    if(parts.size() < 4)
    {
      std::cerr << invalid_format << std::endl;
      csv.close();
      return nodes;
    }
    try
    {
      double x = std::stod(parts[0]);
      double y = std::stod(parts[1]);
      double z = std::stod(parts[2]);
      int type = std::stod(parts[3]);
      if(1 != type)
      {
        continue;
      }
      nodes.push_back(point_type(x, y, z));
    }
    catch(const std::invalid_argument& err)
    {
      std::cerr << invalid_format << std::endl;
      csv.close();
      return nodes;
    }
  }
  csv.close();
  return nodes;
}

int main(int argc, char* argv[])
{
  if(argc != 4)
  {
    std::cerr << invalid_usage << std::endl;
    return -1;
  }
  const std::string file_path = argv[1];
  std::size_t dot = file_path.find_last_of(".");
  const std::string& ext = file_path.substr(dot + 1);
  node_positions_t nodes;
  if("yml" == ext || "yaml" == ext)
  {
    nodes = read_nodes_from_yaml(file_path);
  }
  else if("csv" == ext || "dat" == ext || "txt" == ext)
  {
    nodes = read_nodes_from_csv(file_path);
  }

  if(nodes.empty())
  {
    std::cerr << invalid_format << std::endl;
    return -1;
  }
  double l0 = std::stod(argv[2]);
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << nodes_key;
  out << YAML::Value << YAML::BeginSeq;
  for(std::size_t i = 0; i < nodes.size(); ++i)
  {
    out << YAML::BeginSeq;
    out << nodes[i][0];
    out << nodes[i][1];
    out << nodes[i][2];
    out << YAML::EndSeq;
  }
  out << YAML::EndSeq;
  out << YAML::Key << links_key;
  out << YAML::Value << YAML::BeginSeq;
  for(std::size_t i = 0; i < nodes.size(); ++i)
  {
    for(std::size_t j = i + 1; j < nodes.size(); ++j)
    {
      if(utils::distance(nodes[i], nodes[j]) < l0)
      {
        out << YAML::BeginSeq << i << j << YAML::EndSeq;
      }
    }
  }
  out << YAML::EndMap;
  std::ofstream fout(argv[3]);
  if(!fout.is_open())
  {
    std::cerr << invalid_output_file << std::endl;
    return -1;
  }
  fout << out.c_str() << std::endl;
  fout.close();
  return 0;
}
