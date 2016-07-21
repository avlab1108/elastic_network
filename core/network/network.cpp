#include "network.h"

#include <utils.h>

network::network()
{
}

network::network(const std::size_t size) :
  links_(size*(size - 1)/2)
{
  assert(size > 0);
  nodes_.resize(size);
}

network::network(const node_positions_t& node_positions, const double l0) :
  nodes_(node_positions),
  links_(nodes_.size() * (nodes_.size() - 1)/2)
{
  set_cutoff_distance(l0);
}

network::network(const node_positions_t& node_positions, const links_t& links) :
  nodes_(node_positions),
  links_(nodes_.size() * (nodes_.size() - 1)/2)
{
  set_links(links);
}

network::network(const network& other) :
	nodes_(other.nodes_),
	links_(other.links_)
{
}

void network::set_cutoff_distance(const double l0)
{
  for(std::size_t i = 0; i < get_size(); ++i)
  {
    for(std::size_t j = i + 1; j < get_size(); ++j)
    {
      if(utils::distance(get_node_position(i), get_node_position(j)) < l0)
      {
        add_link(i, j);
      }
    }
  }
}


void network::add_link(const std::size_t node1, const std::size_t node2)
{
  if(node1 == node2)
  {
    return;
  }
  links_.set(node_pair_to_index(node1, node2));
}

const node_positions_t& network::get_node_positions() const
{
  return nodes_;
}

node_positions_t& network::get_node_positions()
{
  return nodes_;
}

void network::set_links(const links_t& links)
{
  for(std::size_t i = 0; i < links.size(); ++i)
  {
    if(links[i].first > get_size() || links[i].second > get_size())
    {
      continue;
    }
    add_link(links[i].first, links[i].second);
  }
}

links_t network::get_links() const
{
  links_t res;
  for(std::size_t i = 0; i < get_size(); ++i)
  {
    for(std::size_t j = i + 1; j < get_size(); ++j)
    {
      if(are_connected(i, j))
      {
        res.push_back(std::make_pair(i, j));
      }
    }
  }
  return res;
}

const point_type& network::get_node_position(const std::size_t node) const
{
  return nodes_[node];
}

void network::set_node_position(const std::size_t node, const point_type& p)
{
  nodes_[node] = p;
}

bool network::are_connected(const std::size_t node1, const std::size_t node2) const
{
  if(node1 == node2)
  {
    return false;
  }
  return links_[node_pair_to_index(node1, node2)];
}

void network::set_size(const std::size_t size)
{
  nodes_.resize(size);
}

const std::size_t network::get_size() const
{
  return nodes_.size();
}

const std::size_t network::node_pair_to_index(const std::size_t node1, const std::size_t node2) const
{
  const std::size_t max = std::max(node1, node2) + 1;
  const std::size_t min = std::min(node1, node2) + 1;
  return min*(min-1)/2 + min*(max-min) + (min > 0 ? (min-1)*(nodes_.size() - max) : 0) - 1;
}
