#include "network_dynamics.h"

#include <cmath>

network_dynamics::network_dynamics(const network& net) :
  net_(net)
{
}

namespace
{
double distance(const point_type& p1, const point_type& p2)
{
  return abs(p1-p2);
}
}

void network_dynamics::operator() (const state_type& x, state_type& dxdt, const double /*t*/)
{
  for(std::size_t i = 0; i < x.size(); ++i)
  {
    dxdt[i][0] = 0.0;
    for(std::size_t j = 0; j < x.size(); ++j)
    {
      double dist_i_j = distance(x[i], x[j]);
      double dist_i_0 = distance(x[i], net_.node_position(i));
      bool a_i_j = net_.are_connected(i, j);
      // x_i
      dxdt[i][0] += a_i_j*(x[i][0] - x[j][0])*(dist_i_j - dist_i_0)/dist_i_j;
      // y_i
      dxdt[i][1] += a_i_j*(x[i][1] - x[j][1])*(dist_i_j - dist_i_0)/dist_i_j;
      // z_i
      dxdt[i][2] += a_i_j*(x[i][2] - x[j][2])*(dist_i_j - dist_i_0)/dist_i_j;
    }
  }
}
