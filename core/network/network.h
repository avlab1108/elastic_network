#pragma once

#include "point.h"

#include <boost/dynamic_bitset.hpp>

#include <vector>

class network
{
public:
  typedef point<double, 3> point_type;

  network(const std::size_t size);

  void add_link(const std::size_t node1, const std::size_t node2);
  const std::vector<point_type>& nodes() const;

  const point_type& node_position(const std::size_t node) const;
  void set_node_position(const std::size_t node, const point_type& p);

private:
  std::vector<point_type> nodes_;
  boost::dynamic_bitset<> links_;
};
