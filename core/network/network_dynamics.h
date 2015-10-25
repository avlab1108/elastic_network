#pragma once

#include "network.h"
#include "point.h"

#include <vector>

class network_dynamics
{
public:
  typedef std::vector<point_type> state_type;

  network_dynamics(const network& net);

  void operator() (const state_type& x, state_type& dxdt, const double /*t*/);

private:
  network net_;
};
