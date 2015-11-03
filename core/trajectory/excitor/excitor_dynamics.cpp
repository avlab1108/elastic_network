#include "excitor_dynamics.h"

#include <iostream>

excitor_dynamics::excitor_dynamics(const network& net, const network::node_positions_type& initial_positions, const forces_type& forces) :
  network_dynamics(net, initial_positions),
  forces_(forces)
{
}

void excitor_dynamics::operator()(const state_type& r, state_type& drdt, const double t)
{
  network_dynamics::operator()(r, drdt, t);
  for(std::size_t i = 0; i < forces_.size(); ++i)
  {
    drdt[forces_[i].first] += forces_[i].second;
  }
}
