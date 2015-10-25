#include "network.h"

network::network(const std::size_t size) :
  links_(size*(size - 1)/2)
{
  nodes_.resize(size);
}

void network::add_link(const std::size_t node1, const std::size_t node2)
{
  const std::size_t max = std::max(node1, node2);
  const std::size_t min = std::min(node1, node2);
  const std::size_t index = min*(min-1)/2 + min*(max-min) + (min > 0 ? (min-1)*(nodes_.size() - max) : 0);
  links_.set(index);
}

const std::vector<point_type>& network::nodes() const
{
  return nodes_;
}

const point_type& network::node_position(const std::size_t node) const
{
  return nodes_[node];
}

void network::set_node_position(const std::size_t node, const point_type& p)
{
  nodes_[node] = p;
}

bool network::are_connected(const std::size_t node1, const std::size_t node2)
{
  const std::size_t max = std::max(node1, node2);
  const std::size_t min = std::min(node1, node2);
  const std::size_t index = min*(min-1)/2 + min*(max-min) + (min > 0 ? (min-1)*(nodes_.size() - max) : 0);
  return links_[index];
}
