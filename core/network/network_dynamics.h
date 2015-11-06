#pragma once

#include "network.h"
#include "point.h"

#include <memory>
#include <vector>

class network_dynamics
{
public:
  typedef std::vector<point_type> state_type;

  network_dynamics(const network& net, const network::node_positions_type& initial_positions);

  void operator() (const state_type& r, state_type& drdt, const double /*t*/);

private:
  network net_;
  network::node_positions_type initial_positions_;
};

typedef std::shared_ptr<network_dynamics> network_dynamics_ptr;
