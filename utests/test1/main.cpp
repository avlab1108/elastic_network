#include <excitor.h>
#include <cstdlib>
#include <iostream>

int main()
{
  network net(64);
  srand(0);
  for(std::size_t i = 0; i < 1000; ++i)
  {
    std::size_t n1 = std::rand() % 64;
    std::size_t n2 = std::rand() % 64;
    while(n2 == n1)
    {
      n2 = std::rand() % 64;
    }
    net.add_link(n1, n2);
  }
  double fs = 5.0;
  std::size_t time = 20;
  std::vector<std::size_t> nodes;
  excitor x(net, fs, time, nodes);
  x.run();
  return 0;
}
