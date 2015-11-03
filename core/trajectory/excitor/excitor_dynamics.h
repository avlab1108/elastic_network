#pragma once

#include <point.h>
#include <network_dynamics.h>

class excitor_dynamics : public network_dynamics
{
public:
  typedef std::vector<std::pair<std::size_t, point_type>> forces_type;

  excitor_dynamics(const network& net, const network::node_positions_type& initial_positions, const forces_type& forces);

  void operator() (const state_type& r, state_type& drdt, const double /*t*/);

private:
  std::vector<std::pair<std::size_t, point_type>> forces_;
};
