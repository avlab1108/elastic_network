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

const network::node_positions_type& network::node_positions() const
{
  return nodes_;
}

network::node_positions_type& network::node_positions()
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

std::size_t network::size() const
{
  return nodes_.size();
}

void setup_links(network& net, const double l0)
{
  for(std::size_t i = 0; i < net.size(); ++i)
  {
    for(std::size_t j = i + 1; j < net.size(); ++j)
    {
      if(distance(net.node_position(i), net.node_position(j)) < l0)
      {
        net.add_link(i, j);
      }
    }
  }
}
