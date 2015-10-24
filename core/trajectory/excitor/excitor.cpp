#include "excitor.h"

excitor::excitor(const network& net, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes) :
  net_(net),
  fs_(fs),
  time_(time),
  nodes_(nodes)
{
}

void excitor::run()
{
}
