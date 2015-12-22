#include <network.h>
#include <utils.h>

#include <cstdlib>
#include <iostream>

int main()
{
  network net(10);
  srand(0);
  for(std::size_t i = 0; i < net.get_size(); ++i)
  {
    net.set_node_position(i, 15*utils::random_point());
  }
  const double l0 = 10;
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
      std::cout << d << std::endl;
      if(d < l0)
      {
        std::cout << "should be connected" << std::endl;
      }
      std::cout << "are connected " << net.are_connected(i, j) << std::endl;
    }
  }
  return 0;
}
