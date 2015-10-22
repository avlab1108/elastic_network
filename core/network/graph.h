#pragma once

#include <boost/dynamic_bitset.hpp>

#include <vector>

struct point
{
	point(const double x0 = 0.0, const double y0 = 0.0, const double z0 = 0.0);
	double x;
	double y;
	double z;
};

typedef point direction;

class network
{
public:
	network(const std::size_t size);

	void add_link(const std::size_t node1, const std::size_t node2);
	const std::vector<point>& nodes() const;

	const point& node_position(const std::size_t node) const;
	void set_node_position(const std::size_t node, const position& p);

private:
	std::vector<point> nodes_;
	boost::dynamic_bitset<> links_;
};
