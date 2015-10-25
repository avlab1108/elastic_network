#include "excitor.h"

#include "force_generator.h"

excitor::excitor(const network& net, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes) :
  net_(net),
  net_dynamics_(net_, force_generator(fs, nodes).generate()),
  fs_(fs),
  time_(time),
  nodes_(nodes)
{
}

void excitor::run()
{
}
