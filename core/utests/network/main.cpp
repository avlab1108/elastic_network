#include <network.h>
#include <utils.h>

#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE IO_UNIT_TEST
#include <boost/test/unit_test.hpp>

#include <cstdlib>

BOOST_AUTO_TEST_SUITE(network_suite)

BOOST_AUTO_TEST_CASE(case1)
{
  network net(15);
  BOOST_CHECK(net.get_size() == 15);
  BOOST_CHECK(net.get_links().empty());
  net.add_link(1, 2);
  BOOST_CHECK(net.are_connected(1, 2));
  BOOST_CHECK(net.are_connected(2, 1));
  net.add_link(0, 14);
  BOOST_CHECK(net.are_connected(0, 14));
  BOOST_CHECK(net.are_connected(14, 0));
  BOOST_CHECK(2 == net.get_links().size());
  point_type p{0.0, 17.0, 4.5};
  net.set_node_position(6, p);
  BOOST_CHECK(net.get_node_position(6)[0] == p[0]);
  BOOST_CHECK(net.get_node_position(6)[1] == p[1]);
  BOOST_CHECK(net.get_node_position(6)[2] == p[2]);
}

BOOST_AUTO_TEST_CASE(case2)
{
  network net(10);
  srand(0);
  for(std::size_t i = 0; i < net.get_size(); ++i)
  {
    net.set_node_position(i, 15*utils::random_point());
  }
  const double l0 = 5;
  net.set_cutoff_distance(l0);
  for(std::size_t i = 0; i < net.get_size(); ++i)
  {
    for(std::size_t j = 0; j < net.get_size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      double d = utils::distance(net.get_node_position(i), net.get_node_position(j));
      if(d < l0)
      {
        BOOST_CHECK(net.are_connected(i, j));
      }
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
