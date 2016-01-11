/**
 * @file utils.h
 * @brief This file contains various utilities.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "point.h"
#include "common_types.h"

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
