#include "network.h"

network::network()
{
}

network::network(const std::size_t size) :
  links_(size*(size - 1)/2)
{
  assert(size > 0);
  nodes_.resize(size);
}

network::network(const node_positions_type& node_positions, const long double l0) :
  nodes_(node_positions),
  links_(nodes_.size() * (nodes_.size() - 1)/2)
{
  set_cutoff_distance(l0);
}

network::network(const node_positions_type& node_positions, const links_type& links) :
  nodes_(node_positions),
  links_(nodes_.size() * (nodes_.size() - 1)/2)
{
  for(std::size_t i = 0; i < links.size(); ++i)
  {
    add_link(links[i].first, links[i].second);
  }
}

void network::set_cutoff_distance(const long double l0)
{
  cutoff_distance_ = l0;
  for(std::size_t i = 0; i < size(); ++i)
  {
    for(std::size_t j = i + 1; j < size(); ++j)
    {
      if(utils::distance(node_position(i), node_position(j)) < l0)
      {
        add_link(i, j);
      }
    }
  }
}

const long double network::cutoff_distance() const
{
  return cutoff_distance_;
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

network::links_type network::links() const
{
  links_type res;
  for(std::size_t i = 0; i < size(); ++i)
  {
    for(std::size_t j = i + 1; j < size(); ++j)
    {
      if(are_connected(i, j))
      {
        res.push_back(std::make_pair(i, j));
      }
    }
  }
  return res;
}

const point_type& network::node_position(const std::size_t node) const
{
  return nodes_[node];
}

void network::set_node_position(const std::size_t node, const point_type& p)
{
  nodes_[node] = p;
}

bool network::are_connected(const std::size_t node1, const std::size_t node2) const
{
  const std::size_t max = std::max(node1, node2);
  const std::size_t min = std::min(node1, node2);
  const std::size_t index = min*(min-1)/2 + min*(max-min) + (min > 0 ? (min-1)*(nodes_.size() - max) : 0);
  return links_[index];
}

void network::set_size(const std::size_t size)
{
  nodes_.resize(size);
}

const std::size_t network::size() const
{
  return nodes_.size();
}
