#include "user_settings_io.h"

#include <utils.h>
#include <logging.h>
#include <common_types.h>

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

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
const std::string invalid_file_type = "Invalid file type provided as " + usc::network_file_path + ".";
const std::string invalid_format    = "Invalid format of network file.";

user_settings_io::user_settings_io()
{
}
 
void user_settings_io::import_settings(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
    settings_file_name_ = file_path;
  }
  catch(YAML::Exception& e)
  {
    const std::string& error = "Failed to load user settings file from \"" + file_path + "\".\n\tError: " + e.what();
    LOG(logger::critical, error);
    throw std::runtime_error(error);
  }

  /// Check input file structure validity
  check_input_validity(node);

  settings_.set_fs(node[usc::fs].as<double>());
  settings_.set_excitation_time(node[usc::excitation_time].as<std::size_t>());
  settings_.set_time_step(node[usc::time_step].as<double>());
  settings_.set_simulations_count(node[usc::simulations_count].as<std::size_t>());

  if(node[usc::force_application_nodes])
  {
    const YAML::Node& force_node = node[usc::force_application_nodes];
    std::vector<std::size_t> nodes;
    for(std::size_t i = 0; i < force_node.size(); ++i)
    {
      std::size_t node = force_node[i].as<std::size_t>();
      nodes.push_back(node);
    }
    settings_.set_force_application_nodes(nodes);
  }

  if(node[usc::visualization_nodes])
  {
    const YAML::Node& visualization_node = node[usc::visualization_nodes];
    std::vector<std::size_t> nodes;
    for(std::size_t i = 0; i < visualization_node.size(); ++i)
    {
      std::size_t node = visualization_node[i].as<std::size_t>();
      nodes.push_back(node);
    }
    settings_.set_visualization_nodes(nodes);
  }

  if(node[usc::nodes])
  {
    settings_.set_network(read_network_from_yaml(node));
  }
  else
  {
    std::string absolute_path = node[usc::network_file_path].as<std::string>();
    if(!absolute_path.empty())
    {
      if(absolute_path[0] != '/')
      {
        //This is relative path, need to attach current YAML file's directory to path
        absolute_path.insert(0, file_path.substr(0, file_path.find_last_of("/") + 1));
      }
      network_file_name_ = absolute_path;
      import_network_from_external_file(absolute_path);
    }
  }

  if(node[usc::l0])
  {
    double cutoff = node[usc::l0].as<double>();
    settings_.set_cutoff_distance(cutoff);
    network net = settings_.get_network();
    net.set_cutoff_distance(cutoff);
    settings_.set_network(net);
  }

  std::cout << settings_ << std::endl;
}

void user_settings_io::export_settings(const std::string& output_dir)
{
  if(!settings_file_name_.empty())
  {
    namespace fs = boost::filesystem;
    std::string config_dir = output_dir + "/config";
    fs::path out_path(config_dir);
    fs::create_directory(out_path);

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << usc::fs;
    out << YAML::Value << settings_.get_fs();

    out << YAML::Key << usc::time_step;
    out << YAML::Value << settings_.get_time_step();

    out << YAML::Key << usc::excitation_time;
    out << YAML::Value << settings_.get_excitation_time();

    out << YAML::Key << usc::simulations_count;
    out << YAML::Value << settings_.get_simulations_count();

    out << YAML::Key << usc::visualization_nodes;
    out << YAML::Value << YAML::BeginSeq;
    const auto& vis_nodes = settings_.get_visualization_nodes();
    for(auto it = vis_nodes.begin(); it != vis_nodes.end(); ++it)
    {
      out << *it;
    }
    out << YAML::EndSeq;

    if(!settings_.get_force_application_nodes().empty())
    {
      out << YAML::Key << usc::force_application_nodes;
      out << YAML::Value << YAML::BeginSeq;
      const auto& force_nodes = settings_.get_force_application_nodes();
      for(auto it = force_nodes.begin(); it != force_nodes.end(); ++it)
      {
        out << *it;
      }
      out << YAML::EndSeq;
    }

    if(settings_.get_cutoff_distance())
    {
      out << YAML::Key << usc::l0;
      out << YAML::Value << *settings_.get_cutoff_distance();
    }
    if(settings_.get_node_positions())
    {
      out << YAML::Key << usc::nodes;
      const node_positions_type& node_positions = *settings_.get_node_positions();
      out << YAML::Value << YAML::BeginSeq;
      for(auto it = node_positions.begin(); it != node_positions.end(); ++it)
      {
        out << YAML::BeginSeq;
        out << (*it)[0];
        out << (*it)[1];
        out << (*it)[2];
        out << YAML::EndSeq;
      }
      out << YAML::EndSeq;
    }
    if(settings_.get_links())
    {
      out << YAML::Key << usc::links;
      out << YAML::Value << YAML::BeginSeq;
      const std::vector<std::pair<std::size_t, std::size_t>>& links = *settings_.get_links();
      for(auto it = links.begin(); it != links.end(); ++it)
      {
        out << YAML::BeginSeq << it->first << it->second << YAML::EndSeq;
      }
      out << YAML::EndSeq;
    }

    if(settings_.get_network_file_path())
    {
      out << YAML::Key << usc::network_file_path;
      /// Output onyl network file name as it will anyway be copied to the same
      /// directory as user config.
      std::string file_name = *settings_.get_network_file_path();
      if(std::string::npos != file_name.find_first_of('/'))
      {
        file_name = file_name.substr(file_name.find_last_of('/')+1);
      }
      out << YAML::Value << file_name;
    }
    out << YAML::EndMap;

    std::ofstream fout(config_dir + "/config.yaml");
    if(!fout.is_open())
    {
      LOG(logger::error, "Cannot create output config file.");
      return;
    }
    fout << out.c_str() << std::endl;
    fout.close();

    if(settings_.get_network_file_path())
    {
      utils::copy_file(*settings_.get_network_file_path(), config_dir);
    }
  }
}

const user_settings& user_settings_io::get_settings() const
{
  return settings_;
}

user_settings& user_settings_io::get_settings()
{
  return settings_;
}

void user_settings_io::check_input_validity(const YAML::Node& node) const
{
  if(!node[usc::simulations_count] ||
    !node[usc::excitation_time] ||
    !node[usc::fs] ||
    !node[usc::time_step])
  {
    LOG(logger::critical, invalid_structure);
    throw std::runtime_error(invalid_structure);
  }
  if(node[usc::nodes])
  {
    if((node[usc::links] && node[usc::l0]) ||
      (!node[usc::links] && !node[usc::l0]) ||
      node[usc::network_file_path])
    {
      LOG(logger::critical, invalid_structure);
      throw std::runtime_error(invalid_structure);
    }
  }
  else
  {
    if(!node[usc::network_file_path])
    {
      LOG(logger::critical, invalid_structure);
      throw std::runtime_error(invalid_structure);
    }
  }
}

void user_settings_io::import_network_from_external_file(const std::string& file_path)
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
  settings_.set_network_file_path(file_path);
}

network user_settings_io::read_network_from_yaml(const YAML::Node& node)
{
  const YAML::Node& nodes = node[usc::nodes];
  const std::size_t size = nodes.size();
  network net(size);
  node_positions_type node_positions;
  for(std::size_t i = 0; i < size; ++i)
  {
    const point_type& position = nodes[i].as<point_type>();
    net.set_node_position(i, position);
    node_positions.push_back(position);
  }
  settings_.set_node_positions(node_positions);
  if(node[usc::links])
  {
    std::vector<std::pair<std::size_t, std::size_t>> links;
    const YAML::Node& links_node = node[usc::links];
    for(std::size_t i = 0; i < links_node.size(); ++i)
    {
      std::pair<std::size_t, std::size_t> link = links_node[i].as<std::pair<std::size_t, std::size_t>>();
      links.push_back(link);
      net.add_link(link.first, link.second);
    }
    settings_.set_links(links);
  }
  return net;
}

network user_settings_io::read_network_from_yaml_file(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    const std::string& error = "Failed to load network from \"" + file_path + "\".\n\tError: " + e.what();
    LOG(logger::critical, error);
    throw std::runtime_error(error);
  }
  return read_network_from_yaml(node);
}

network user_settings_io::read_network_from_csv_file(const std::string& file_path)
{
  std::ifstream csv(file_path);
  if(!csv.is_open())
  {
    LOG(logger::critical, invalid_file_type);
    throw std::runtime_error(invalid_file_type);
  }
  std::string line;
  node_positions_type nodes;
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
      throw std::runtime_error(invalid_format);
    }
  }
  network net(nodes.size());
  for(std::size_t i = 0; i < nodes.size(); ++i)
  {
    net.set_node_position(i, nodes[i]);
  }
  return net;
}
