#include "utils.h"
#include "logging.h"

#include <network.h>

#include <boost/filesystem.hpp>

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
    std::cerr << "Error openning output file \"" << file_name << "\"" << std::endl;
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
    std::cerr << "Error openning output file \"" << file_name << "\"" << std::endl;
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
