#pragma once

#include "point.h"

class network;

namespace utils
{

point_type random_point();

double distance(const point_type& p1, const point_type& p2);

void dump_adjacency_list(const network& net, const std::string& file_name);
void dump_adjacency_matrix(const network& net, const std::string& file_name);

void create_directory(const std::string& dir);

void copy_file(const std::string& source, const std::string& destination);

}
