#include "user_settings_io.h"

#include <utils.h>
#include <logging.h>
#include <common_types.h>

#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>

#include <yaml-cpp/yaml.h>
#include <string>

#include <iostream>

const std::string invalid_structure = "Invalid structure of user config file.";
const std::string invalid_file_type = "Invalid file type provided as " + usc::network_file_path + ".";
const std::string invalid_network = "Invalid structure of network file.";
const std::string invalid_equilibrium_state_spec = "Invalid structure of equilibrium state specification file.";

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
  settings_.set_excitation_time_step(node[usc::excitation_time_step].as<double>());
  YAML::Node spec_node = node[usc::rtss::self];
  relaxation_time_step_spec spec(spec_node[usc::rtss::initial_step].as<double>(), spec_node[usc::rtss::time_delta].as<std::size_t>(), spec_node[usc::rtss::coefficient].as<double>());
  settings_.set_relaxation_time_step_spec(spec);
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
  settings_.set_forces_dynamic(node[usc::forces_dynamic].as<bool>());

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

  import_network_from_external_file(node);

  import_equilibrium_state_spec(node);

  std::cout << settings_ << std::endl;
}

void user_settings_io::export_settings(const std::string& output_dir)
{
  if(!settings_file_name_.empty())
  {
    std::string config_dir = output_dir + "/config";
    utils::create_directory(config_dir);

    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << usc::fs;
    out << YAML::Value << settings_.get_fs();

    out << YAML::Key << usc::forces_dynamic;
    out << YAML::Value << settings_.get_forces_dynamic();

    out << YAML::Key << usc::excitation_time_step;
    out << YAML::Value << settings_.get_excitation_time_step();

    out << YAML::Key << usc::excitation_time;
    out << YAML::Value << settings_.get_excitation_time();

    out << YAML::Key << usc::rtss::self;
    out << YAML::BeginMap;
    out << YAML::Key << usc::rtss::initial_step;
    out << YAML::Value << settings_.get_relaxation_time_step_spec().initial_step;
    out << YAML::Key << usc::rtss::time_delta;
    out << YAML::Value << settings_.get_relaxation_time_step_spec().time_delta;
    out << YAML::Key << usc::rtss::coefficient;
    out << YAML::Value << settings_.get_relaxation_time_step_spec().coefficient;
    out << YAML::EndMap;

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

    out << YAML::Key << usc::network_file_path;
    /**
     * @note Output only network file name as it will anyway be copied to the same directory as user config.
     */
    std::string file_name = settings_.get_network_file_path();
    if(std::string::npos != file_name.find_first_of('/'))
    {
      file_name = file_name.substr(file_name.find_last_of('/')+1);
    }
    out << YAML::Value << file_name;
    out << YAML::EndMap;

    std::ofstream fout(config_dir + "/config.yaml");
    if(!fout.is_open())
    {
      LOG(logger::error, "Cannot create output config file.");
      return;
    }
    fout << out.c_str() << std::endl;
    fout.close();

    utils::copy_file(settings_.get_network_file_path(), config_dir);
    if(settings_.get_equilibrium_state_spec_file_path())
    {
      utils::copy_file(*settings_.get_equilibrium_state_spec_file_path(), config_dir);
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
    !node[usc::excitation_time_step] ||
    !node[usc::forces_dynamic] ||
    !node[usc::rtss::self] ||
    !node[usc::network_file_path])
  {
    LOG(logger::critical, invalid_structure);
    throw std::runtime_error(invalid_structure);
  }

  if(!node[usc::rtss::self][usc::rtss::initial_step] ||
    !node[usc::rtss::self][usc::rtss::time_delta] ||
    !node[usc::rtss::self][usc::rtss::coefficient])
  {
    LOG(logger::critical, invalid_structure);
    throw std::runtime_error(invalid_structure);
  }
}

void user_settings_io::import_network_from_external_file(const YAML::Node& node)
{
  std::string absolute_path = node[usc::network_file_path].as<std::string>();
  if(absolute_path.empty())
  {
    // TODO report error
    return;
  }
  if(absolute_path[0] != '/')
  {
    //This is relative path, need to attach current YAML file's directory to path
    absolute_path.insert(0, settings_file_name_.substr(0, settings_file_name_.find_last_of("/") + 1));
  }

  std::size_t dot = absolute_path.find_last_of(".");
  const std::string& ext = absolute_path.substr(dot + 1);
  if("yml" == ext || "yaml" == ext)
  {
    settings_.set_network(read_network_from_yaml_file(absolute_path));
  }
  else
  {
    LOG(logger::critical, invalid_file_type);
    throw std::runtime_error(invalid_file_type);
  }
  settings_.set_network_file_path(absolute_path);
}

void user_settings_io::import_equilibrium_state_spec(const YAML::Node& node)
{
  node_positions_t positions;
  node_distances_t distances;
	if(node[usc::equilibrium_state])
	{
    std::string absolute_path = node[usc::equilibrium_state].as<std::string>();
    if(!absolute_path.empty())
    {
      if(absolute_path[0] != '/')
      {
        //This is relative path, need to attach current YAML file's directory to path
        absolute_path.insert(0, settings_file_name_.substr(0, settings_file_name_.find_last_of("/") + 1));
      }
      std::size_t dot = absolute_path.find_last_of(".");
      const std::string& ext = absolute_path.substr(dot + 1);
      if("yml" == ext || "yaml" == ext)
      {
        settings_.set_equilibrium_state_spec(read_equilibrium_state_from_yaml_file(absolute_path));
      }
      else
      {
        LOG(logger::critical, invalid_file_type);
        throw std::runtime_error(invalid_file_type);
      }
    }
    settings_.set_equilibrium_state_spec_file_path(absolute_path);
  }
}

network user_settings_io::read_network_from_yaml(const YAML::Node& node)
{
  if(!node[usc::nodes] || !node[usc::links])
  {
    LOG(logger::critical, invalid_network);
    throw std::runtime_error(invalid_network);
  }
  const YAML::Node& nodes = node[usc::nodes];
  const std::size_t size = nodes.size();
  network net(size);
  for(std::size_t i = 0; i < size; ++i)
  {
    const point_type& position = nodes[i].as<point_type>();
    net.set_node_position(i, position);
  }
  const YAML::Node& links = node[usc::links];
  for(std::size_t i = 0; i < links.size(); ++i)
  {
    std::pair<std::size_t, std::size_t> link = links[i].as<std::pair<std::size_t, std::size_t>>();
    net.add_link(link.first, link.second);
  }
  return net;
}

equilibrium_state_spec user_settings_io::read_equilibrium_state_from_yaml(const YAML::Node& node)
{
  if(!node[usc::nodes] || !node[usc::equilibrium_distances])
  {
    LOG(logger::critical, invalid_equilibrium_state_spec);
    throw std::runtime_error(invalid_equilibrium_state_spec);
  }

  node_positions_t positions;
  node_distances_t distances;

  const YAML::Node& nodes = node[usc::nodes];
  const std::size_t size = nodes.size();
  for(std::size_t i = 0; i < size; ++i)
  {
    positions.push_back(nodes[i].as<point_type>());
  }
  const YAML::Node& dists = node[usc::equilibrium_distances];
  for(YAML::const_iterator it = dists.begin(); it != dists.end(); ++it)
  {
    YAML::Node key = it->first;
    if(2 != key.size())
    {
      LOG(logger::critical, invalid_structure);
      throw std::runtime_error(invalid_structure);
    }
    std::size_t node1, node2;
    node1 = key[0].as<std::size_t>();
    node2 = key[1].as<std::size_t>();
    double value = it->second.as<double>();
    distances[std::make_pair(node1, node2)] = value;
  }
  return equilibrium_state_spec{positions, distances};
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

equilibrium_state_spec user_settings_io::read_equilibrium_state_from_yaml_file(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    const std::string& error = "Failed to load equilibrium state specification from \"" + file_path + "\".\n\tError: " + e.what();
    LOG(logger::critical, error);
    throw std::runtime_error(error);
  }
  return read_equilibrium_state_from_yaml(node);
}
