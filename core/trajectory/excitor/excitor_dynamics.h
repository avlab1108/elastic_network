#pragma once

#include <point.h>
#include <network_dynamics.h>

class excitor_dynamics : public network_dynamics
{
public:
  typedef std::vector<std::pair<std::size_t, point_type>> forces_type;

  excitor_dynamics(const network& net, const forces_type& forces);

  void operator() (const state_type& x, state_type& dxdt, const double /*t*/);

private:
  std::vector<std::pair<std::size_t, point_type>> forces_;
};
