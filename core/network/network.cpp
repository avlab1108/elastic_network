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

const std::vector<point_type>& network::node_positions() const
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

void network::setup_links(const double l0)
{
  for(std::size_t i = 0; i < size(); ++i)
  {
    for(std::size_t j = 0; j < size(); ++j)
    {
      if(distance(node_position(i), node_position(j)) < l0)
      {
        add_link(i, j);
      }
    }
  }
}

std::size_t network::size() const
{
  return nodes_.size();
}
