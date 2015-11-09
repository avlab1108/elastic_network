#include "importer.h"

#include <utils.h>

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

importer::importer(const std::string& file_path)
{
  YAML::Node node = YAML::LoadFile(file_path);
  if(node[constants::fs])
  {
    settings_.set_fs(node[constants::fs].as<double>());
  }

  if(node[constants::nodes])
  {
    if((node[constants::links] && node[constants::l0]) ||
      (!node[constants::links] && !node[constants::l0]) ||
      node[constants::networkFilePath])
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
    if(node[constants::networkFilePath])
    {
      import_network_from_external_file(node[constants::networkFilePath].as<std::string>());
    }
  }
}

void importer::read_network_from_yaml(const YAML::Node& node)
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

void importer::import_network_from_external_file(const std::string& file_path)
{
  std::size_t dot = file_path.find_last_of(".");
  const std::string& ext = file_path.substr(dot + 1);
  if(".yml" == ext || ".yaml" == ext)
  {
    import_network_from_yaml_file(file_path);
  }
  else if(".csv" == ext || ".dat" == ext || ".txt" == ext)
  {
    import_network_from_csv_file(file_path);
  }
  else
  {
    throw std::runtime_error("Invalid file type provided as " + constants::networkFilePath);
  }
}

void importer::import_network_from_yaml_file(const std::string& file_path)
{
  YAML::Node node = YAML::LoadFile(file_path);
  read_network_from_yaml(node);
}

void importer::import_network_from_csv_file(const std::string& file_path)
{
}
