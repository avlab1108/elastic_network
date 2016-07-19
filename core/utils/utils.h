/**
 * @file utils.h
 * @brief This file contains various utilities.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "point.h"
#include "common_types.h"

#include <yaml-cpp/yaml.h>

class network;

namespace utils
{

/**
 * @brief Generates random point.
 * @return Random point.
 */
point_type random_point();

/**
 * @brief Calculates distance between provided points.
 * @param p1 First point.
 * @param p2 Second point.
 * @return Distance values.
 */
double distance(const point_type& p1, const point_type& p2);

/**
 * @brief Dumps provided network to the specified file as adjacency list.
 * @param net Network.
 * @param file_name Output file name.
 */
void dump_adjacency_list(const network& net, const std::string& file_name);
/**
 * @brief Dumps provided network to the specified file as adjacency matrix.
 * @param net Network.
 * @param file_name Output file name.
 */
void dump_adjacency_matrix(const network& net, const std::string& file_name);
/**
 * @brief Dumps network to outpt file in YAML format.
 * @param net Network.
 * @param file_name Output file name.
 */
void dump_yaml(const network& net, const std::string& file_name);

/**
 * @brief Creates directory with specified name.
 * @param dir Directory name.
 */
void create_directory(const std::string& dir);

/**
 * @brief Copies source file to destination.
 * @param source Source file.
 * @param destination Destination file.
 */
void copy_file(const std::string& source, const std::string& destination);

}

namespace YAML
{
/**
 * @brief Specialization of YAML::convert struct to allow point_type serialization/deserialization.
 */
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
