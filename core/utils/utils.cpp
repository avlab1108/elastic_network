#include "utils.h"

#include <network.h>

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
  const network::links_type& links = net.get_links();
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

}
