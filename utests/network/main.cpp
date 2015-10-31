#include <network.h>
#include <cstdlib>
#include <iostream>

int main()
{
  network net(10);
  srand(0);
  for(std::size_t i = 0; i < net.size(); ++i)
  {
    net.set_node_position(i, 15*random_point());
  }
  const double l0 = 10;
  setup_links(net, l0);
  for(std::size_t i = 0; i < net.size(); ++i)
  {
    for(std::size_t j = 0; j < net.size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      long double d = distance(net.node_position(i), net.node_position(j));
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
