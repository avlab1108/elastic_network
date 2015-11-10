#pragma once

#include "point.h"

class network;

namespace utils
{

point_type random_point();

long double distance(const point_type& p1, const point_type& p2);

void dump_adjacency_list(const network& net, const std::string& file_name);

}
