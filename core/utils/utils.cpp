#include "utils.h"
#include "logging.h"

#include <network.h>

#include <yaml-cpp/yaml.h>

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS

#include <iostream>
#include <fstream>
#include <random>

namespace utils
{

point_type random_point()
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis(-0.5, 0.5);
  double x = dis(gen);
  double y = dis(gen);
  double z = dis(gen);
  return point_type(x, y, z);
}

double distance(const point_type& p1, const point_type& p2)
{
  return abs(p1-p2);
}

void dump_adjacency_list(const network& net, const std::string& file_name)
{
  std::ofstream out(file_name);
  if(!out.is_open())
  {
    LOG(logger::error, std::string("Error openning output file \"") + file_name + "\".");
    return;
  }
  const links_t& links = net.get_links();
  for(std::size_t i = 0; i < links.size(); ++i)
  {
    out << links[i].first << " " << links[i].second << std::endl;
  }
  out.close();
}

void dump_adjacency_matrix(const network& net, const std::string& file_name)
{
  std::ofstream out(file_name);
  if(!out.is_open())
  {
    LOG(logger::error, std::string("Error openning output file \"") + file_name + "\".");
    return;
  }
  for(std::size_t i = 0; i < net.get_size(); ++i)
  {
    for(std::size_t j = 0; j < net.get_size(); ++j)
    {
      out << (net.are_connected(i, j) ? "1," : "0,");
    }
    out << std::endl;
  }
  out.close();
}

namespace
{
/// Output YAML file keys.
const std::string nodes_key = "nodes";
const std::string links_key = "links";
}

void dump_yaml(const network& net, const std::string& file_name)
{
  std::ofstream fout(file_name);
  if(!fout.is_open())
  {
    LOG(logger::error, std::string("Error openning output file \"") + file_name + "\".");
    return;
  }
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << nodes_key;
  out << YAML::Value << YAML::BeginSeq;
  auto nodes = net.get_node_positions();
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
  auto links = net.get_links();
  for(auto it = links.begin(); it != links.end(); ++it)
  {
    out << YAML::BeginSeq << it->first << it->second << YAML::EndSeq;
  }
  out << YAML::EndMap;
  fout << out.c_str() << std::endl;
  fout.close();
}

void create_directory(const std::string& dir)
{
  boost::filesystem::path path(dir);
  if(boost::filesystem::is_directory(path))
  {
    LOG(logger::info, std::string("Directory \"") + dir + "\" already exists. Trying to use it.");
  }
  else if(!boost::filesystem::create_directory(path))
  {
    LOG(logger::error, std::string("Failed to create directory\"") + dir + "\".");
  }
}

void copy_file(const std::string& source, const std::string& destination)
{
  namespace fs = boost::filesystem;
  std::string file_name = source;
  std::size_t last_slash = source.find_last_of("/");
  if(std::string::npos != last_slash)
  {
    file_name = source.substr(last_slash);
  }
  const std::string& out = destination + file_name;

  fs::copy_file(boost::filesystem::path(source), boost::filesystem::path(out), fs::copy_option::overwrite_if_exists);
}

}
