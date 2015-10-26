#include <excitor.h>
#include <cstdlib>
#include <iostream>

int main()
{
  network net(10);
  srand(0);
  for(std::size_t i = 0; i < net.size(); ++i)
  {
    net.set_node_position(i, 20*random_point());
  }
  const double fs = 0.2;
  const std::size_t time = 10000;
  const double l0 = 3;
  net.setup_links(l0);
  std::vector<std::size_t> nodes;
  nodes.push_back(1);
  nodes.push_back(2);
  excitor x(net, fs, time, nodes);
  x.run();
  return 0;
}
