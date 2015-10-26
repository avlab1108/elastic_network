#include "network_dynamics.h"

#include <cmath>

network_dynamics::network_dynamics(const network& net) :
  net_(net)
{
}

void network_dynamics::operator() (const state_type& x, state_type& dxdt, const double /*t*/)
{
  for(std::size_t i = 0; i < dxdt.size(); ++i)
  {
    dxdt[i] = point_type(0.0, 0.0, 0.0);
    for(std::size_t j = 0; j < x.size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      double dist_i_j = distance(x[i], x[j]);
      double dist_i_0_j_0 = distance(net_.node_position(i), net_.node_position(j));
      bool a_i_j = net_.are_connected(i, j);
      dxdt[i] += static_cast<std::size_t>(a_i_j)*(x[i] - x[j])*(dist_i_j - dist_i_0_j_0)/dist_i_j;
    }
  }
}
