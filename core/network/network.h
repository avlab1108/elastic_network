#pragma once

#include <point.h>
#include <utils.h>

#include <boost/dynamic_bitset.hpp>

#include <vector>

class network
{
public:
  typedef std::vector<point_type> node_positions_type;
  typedef std::vector<std::pair<std::size_t, std::size_t>> links_type;

public:
  network();
  network(const std::size_t size);
  network(const node_positions_type& node_positions, const double l0);
  network(const node_positions_type& node_positions, const links_type& links);

  void set_cutoff_distance(const double l0);

  void add_link(const std::size_t node1, const std::size_t node2);

  const node_positions_type& get_node_positions() const;
  node_positions_type& get_node_positions();

  void set_links(const links_type& links);
  links_type get_links() const;

  const point_type& get_node_position(const std::size_t node) const;
  void set_node_position(const std::size_t node, const point_type& p);

  bool are_connected(const std::size_t node1, const std::size_t node2) const;

  void set_size(const std::size_t size);
  const std::size_t get_size() const;

private:
  const std::size_t node_pair_to_index(const std::size_t node1, const std::size_t node2);

private:
  node_positions_type nodes_;
  boost::dynamic_bitset<> links_;
};
