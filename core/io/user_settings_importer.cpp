#include "user_settings_importer.h"

#include <utils.h>
#include <logging.h>

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include <yaml-cpp/yaml.h>
#include <string>

#include <iostream>

namespace YAML
{
template<>
struct convert<point_type>
{
  static Node encode(const point_type& rhs)
  {
    Node node;
    node.push_back(rhs[0]);
    node.push_back(rhs[1]);
    node.push_back(rhs[2]);
    return node;
  }

  static bool decode(const Node& node, point_type& rhs)
  {
    if(!node.IsSequence() || node.size() != 3)
    {
      return false;
    }

    rhs[0] = node[0].as<point_type::value_type>();
    rhs[1] = node[1].as<point_type::value_type>();
    rhs[2] = node[2].as<point_type::value_type>();
    return true;
  }
};
}

const std::string invalid_structure = "Invalid structure of user config file.";
const std::string invalid_file_type = "Invalid file type provided as " + constants::network_file_path + ".";
const std::string invalid_format    = "Invalid format of network file.";

user_settings_importer::user_settings_importer(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    LOG(logger::critical, std::string("Failed to load user settings file from \"") + file_path + "\".\n\tError: " + e.what());
    throw;
  }
  if(node[constants::fs])
  {
    settings_.set_fs(node[constants::fs].as<double>());
  }

  if(node[constants::time_step])
  {
    settings_.set_time_step(node[constants::time_step].as<double>());
  }

  if(node[constants::time_limit])
  {
    settings_.set_time_limit(node[constants::time_limit].as<size_t>());
  }

  if(node[constants::excitation_time])
  {
    settings_.set_excitation_time(node[constants::excitation_time].as<std::size_t>());
  }

  if(node[constants::simulations_count])
  {
    settings_.set_simulations_count(node[constants::simulations_count].as<std::size_t>());
  }

  if(node[constants::force_application_nodes])
  {
    const YAML::Node& force_node = node[constants::force_application_nodes];
    std::vector<std::size_t> nodes;
    for(std::size_t i = 0; i < force_node.size(); ++i)
    {
      std::size_t node = force_node[i].as<std::size_t>();
      nodes.push_back(node);
    }
    settings_.set_force_application_nodes(nodes);
  }

  if(node[constants::visualization_nodes])
  {
    const YAML::Node& visualization_node = node[constants::visualization_nodes];
    std::vector<std::size_t> nodes;
    for(std::size_t i = 0; i < visualization_node.size(); ++i)
    {
      std::size_t node = visualization_node[i].as<std::size_t>();
      nodes.push_back(node);
    }
    settings_.set_visualization_nodes(nodes);
  }

  // Sanity checkings
  if(node[constants::nodes])
  {
    if((node[constants::links] && node[constants::l0]) ||
      (!node[constants::links] && !node[constants::l0]) ||
      node[constants::network_file_path])
    {
      LOG(logger::critical, invalid_structure);
      throw std::runtime_error(invalid_structure);
    }
  }

  if(node[constants::nodes])
  {
    read_network_from_yaml(node);
  }
  else if(node[constants::network_file_path])
  {
    std::string absolute_path = node[constants::network_file_path].as<std::string>();
    if(!absolute_path.empty())
    {
      if(absolute_path[0] != '/')
      {
        //This is relative path, need to attach current YAML file's directory to path
        absolute_path.insert(0,  file_path.substr(0, file_path.find_last_of("/") + 1));
      }
      import_network_from_external_file(absolute_path);
    }
  }

  if(node[constants::l0])
  {
    double cutoff = node[constants::l0].as<double>();
    network net = settings_.get_network();
    net.set_cutoff_distance(cutoff);
    settings_.set_network(net);
  }
  std::cout << settings_ << std::endl;
}

const user_settings& user_settings_importer::get_settings() const
{
  return settings_;
}

void user_settings_importer::import_network_from_external_file(const std::string& file_path)
{
  std::size_t dot = file_path.find_last_of(".");
  const std::string& ext = file_path.substr(dot + 1);
  if("yml" == ext || "yaml" == ext)
  {
    settings_.set_network(read_network_from_yaml_file(file_path));
  }
  else if("csv" == ext || "dat" == ext || "txt" == ext)
  {
    settings_.set_network(read_network_from_csv_file(file_path));
  }
  else
  {
    LOG(logger::critical, invalid_file_type);
    throw std::runtime_error(invalid_file_type);
  }
}

network user_settings_importer::read_network_from_yaml(const YAML::Node& node)
{
  if(!node[constants::nodes])
  {
    LOG(logger::critical, invalid_format);
    throw std::runtime_error(invalid_format);
  }
  const YAML::Node& nodes = node[constants::nodes];
  const std::size_t size = nodes.size();
  network net(size);
  for(std::size_t i = 0; i < size; ++i)
  {
    net.set_node_position(i, nodes[i].as<point_type>());
  }
  if(node[constants::links])
  {
    const YAML::Node& links_node = node[constants::links];
    for(std::size_t i = 0; i < links_node.size(); ++i)
    {
      std::pair<std::size_t, std::size_t> link = links_node[i].as<std::pair<std::size_t, std::size_t>>();
      net.add_link(link.first - 1, link.second - 1);
    }
  }
  return net;
}

network user_settings_importer::read_network_from_yaml_file(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    LOG(logger::critical, std::string("Failed to load network from \"") + file_path + "\".\n\tError: " + e.what());
    throw;
  }
  return read_network_from_yaml(node);
}

network user_settings_importer::read_network_from_csv_file(const std::string& file_path)
{
  std::ifstream csv(file_path);
  if(!csv.is_open())
  {
    LOG(logger::critical, invalid_file_type);
    throw std::runtime_error(invalid_file_type);
  }
  std::string line;
  network::node_positions_type nodes;
  while(std::getline(csv, line))
  {
    std::vector<std::string> parts;
    boost::split(parts, line, boost::is_any_of(" \t"), boost::token_compress_on);
    if(parts.size() < 4)
    {
      LOG(logger::critical, invalid_format);
      throw std::runtime_error(invalid_format);
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
      //TODO maybe process?
      LOG(logger::critical, invalid_format);
      throw;
    }
  }
  std::cout << __FUNCTION__ << nodes.size() << std::endl;
  network net(nodes.size());
  for(std::size_t i = 0; i < nodes.size(); ++i)
  {
    net.set_node_position(i, nodes[i]);
  }
  return net;
}
