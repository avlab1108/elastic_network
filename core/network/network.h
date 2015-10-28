#pragma once

#include "point.h"

#include <boost/dynamic_bitset.hpp>

#include <vector>

class network
{
public:
  network(const std::size_t size);

  void add_link(const std::size_t node1, const std::size_t node2);
  const std::vector<point_type>& node_positions() const;

  const point_type& node_position(const std::size_t node) const;
  void set_node_position(const std::size_t node, const point_type& p);

  bool are_connected(const std::size_t node1, const std::size_t node2);

  std::size_t size() const;

private:
  std::vector<point_type> nodes_;
  boost::dynamic_bitset<> links_;
};

void setup_links(network& net, const double l0);

