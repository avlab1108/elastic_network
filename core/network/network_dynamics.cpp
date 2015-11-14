#include "network_dynamics.h"

#include <utils.h>

#include <cmath>

network_dynamics::network_dynamics(const network& net, const network::node_positions_type& initial_positions) :
  net_(net),
  initial_positions_(initial_positions)
{
}

void network_dynamics::calculate(const state_type& r, state_type& drdt, const double t)
{
  assert(drdt.size() == net_.get_size());
  for(std::size_t i = 0; i < drdt.size(); ++i)
  {
    drdt[i] = point_type(0.0, 0.0, 0.0);
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      bool a_i_j = net_.are_connected(i, j);
      if(a_i_j)
      {
        double dist_i_j = utils::distance(r[i], r[j]);
        double dist_i0_j0 = utils::distance(initial_positions_[i], initial_positions_[j]);
        drdt[i] -= (r[i] - r[j])*(dist_i_j - dist_i0_j0)/dist_i_j;
      }
    }
  }
}

void network_dynamics::prepare_for_step()
{
}

network_dynamics_wrapper::network_dynamics_wrapper(const std::shared_ptr<network_dynamics>& dynamics) :
  dynamics_(dynamics)
{
  assert(dynamics_);
}

void network_dynamics_wrapper::operator() (const state_type& r, state_type& drdt, const double t)
{
  dynamics_->calculate(r, drdt, t);
}

void network_dynamics_wrapper::prepare_for_step()
{
  dynamics_->prepare_for_step();
}
