#include "user_settings_importer.h"

#include <utils.h>
#include <logging.h>

#include <yaml-cpp/yaml.h>

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

user_settings_importer::user_settings_importer(const std::string& file_path)
{
  YAML::Node node;
  try
  {
    node = YAML::LoadFile(file_path);
  }
  catch(YAML::Exception& e)
  {
    LOG(logger::error, std::string("Failed to load user settings file from \"") + file_path + "\".\n\tError: " + e.what());
    return;
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

  //TODO: read nodes from file

  if(node[constants::nodes])
  {
    if((node[constants::links] && node[constants::l0]) ||
      (!node[constants::links] && !node[constants::l0]) ||
      node[constants::network_file_path])
    {
      throw std::runtime_error("Invalid structure of file.");
    }
  }

  if(node[constants::nodes])
  {
    read_network_from_yaml(node);
  }
  else
  {
    if(node[constants::network_file_path])
    {
      import_network_from_external_file(node[constants::network_file_path].as<std::string>());
    }
  }
}

const user_settings& user_settings_importer::get_settings() const
{
  return settings_;
}

void user_settings_importer::read_network_from_yaml(const YAML::Node& node)
{
  const YAML::Node& nodes = node[constants::nodes];
  const std::size_t size = nodes.size();
  network net(size);
  for(std::size_t i = 0; i < size; ++i)
  {
    net.set_node_position(i, nodes[i].as<point_type>());
  }
  if(node[constants::l0])
  {
    net.set_cutoff_distance(node[constants::l0].as<double>());
  }
  else
  {
    assert(node[constants::links]);
    const YAML::Node& links_node = node[constants::links];
    for(std::size_t i = 0; i < links_node.size(); ++i)
    {
      std::pair<std::size_t, std::size_t> link = links_node[i].as<std::pair<std::size_t, std::size_t>>();
      net.add_link(link.first - 1, link.second - 1);
    }
  }
  settings_.set_network(net);
}

void user_settings_importer::import_network_from_external_file(const std::string& file_path)
{
  std::size_t dot = file_path.find_last_of(".");
  const std::string& ext = file_path.substr(dot + 1);
  if("yml" == ext || "yaml" == ext)
  {
    import_network_from_yaml_file(file_path);
  }
  else if("csv" == ext || "dat" == ext || "txt" == ext)
  {
    import_network_from_csv_file(file_path);
  }
  else
  {
    throw std::runtime_error("Invalid file type provided as " + constants::network_file_path);
  }
}

void user_settings_importer::import_network_from_yaml_file(const std::string& file_path)
{
  YAML::Node node = YAML::LoadFile(file_path);
  read_network_from_yaml(node);
}

void user_settings_importer::import_network_from_csv_file(const std::string& file_path)
{
}
