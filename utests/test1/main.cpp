#include <excitor.h>
#include <relaxer.h>
#include <cstdlib>

int main()
{
  network net(10);
  srand(0);
  for(std::size_t i = 0; i < net.size(); ++i)
  {
    net.set_node_position(i, 15*random_point());
  }
  const double fs = 0.2;
  const std::size_t time = 10;
  const double l0 = 10;
  setup_links(net, l0);
  std::vector<std::size_t> nodes;
  nodes.push_back(1);
  nodes.push_back(5);
  nodes.push_back(9);
  excitor x(net, fs, time, nodes);
  x.run();
  relaxer r(net, 10000);
  r.run();
  return 0;
}
