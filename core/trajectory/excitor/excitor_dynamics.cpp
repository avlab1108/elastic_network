#include "excitor_dynamics.h"

excitor_dynamics::excitor_dynamics(const network& net, const forces_type& forces) :
  network_dynamics(net),
  forces_(forces)
{
}

void excitor_dynamics::operator()(const state_type& x, state_type& dxdt, const double t)
{
  network_dynamics::operator()(x, dxdt, t);
  for(std::size_t i = 0; i < forces_.size(); ++i)
  {
    dxdt[forces_[i].first] += forces_[i].second;
  }
}
