#include "network_dynamics.h"

#include <cmath>
#include <iostream>

network_dynamics::network_dynamics(const network& net, const network::node_positions_type& initial_positions) :
  net_(net),
  initial_positions_(initial_positions)
{
}

void network_dynamics::operator() (const state_type& r, state_type& drdt, const double /*t*/)
{
  assert(drdt.size() == net_.size());
  for(std::size_t i = 0; i < drdt.size(); ++i)
  {
    drdt[i] = point_type(0.0, 0.0, 0.0);
    for(std::size_t j = 0; j < net_.size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      bool a_i_j = net_.are_connected(i, j);
      if(a_i_j)
      {
        double dist_i_j = distance(r[i], r[j]);
        double dist_i0_j0 = distance(initial_positions_[i], initial_positions_[j]);
        drdt[i] += -(r[i] - r[j]) - dist_i0_j0/dist_i_j;
      }
    }
  }
}
