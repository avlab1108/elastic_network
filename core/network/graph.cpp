#include "network.h"

point::point(const double x, const double y, const double z) :
	x(x0),
	y(y0),
	z(z0)
{
}

network::network(const std::size_t size) :
	links_(size*(size - 1)/2)
{
	nodes_.resize(size);
}

void network::add_link(const std::size_t node1, const std::size_t node2)
{
	const std::size_t max = std::max(node1, node2);
	const std::size_t min = std::min(node1, node2);
	links_[min*nodes_.size() - (min-1)*min/2 + max - min].set();
}

const std::vector<point>& network::nodes() const
{
	return nodes_;
}

const point& network::node_position(const std::size_t node) const
{
	return nodes_[node];
}

void network::set_node_position(const std::size_t node, const position& p)
{
	nodes_[node] = position;
}
