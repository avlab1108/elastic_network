#include <excitor.h>

int main()
{
  network net(64);
  for(std::size_t i = 0; i < 12; ++i)
  {
    for(std::size_t j = 34; j < 45; ++j)
    {
      net.add_link(i, j);
    }
  }
  double fs = 5.0;
  std::size_t time = 20000;
  std::vector<std::size_t> nodes;
  excitor x(net, fs, time, nodes);
  x.run();
  return 0;
}
