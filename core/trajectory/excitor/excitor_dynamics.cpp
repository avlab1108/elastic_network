#include "excitor_dynamics.h"

excitor_dynamics::excitor_dynamics(const network& net, const node_positions_type& initial_positions, const forces_spec& fspec) :
  network_dynamics(net, initial_positions),
  fspec_(fspec),
  generator_(fspec)
{
}

void excitor_dynamics::calculate(const state_type& r, state_type& drdt, const double t)
{
  network_dynamics::calculate(r, drdt, t);
  for(std::size_t i = 0; i < forces_.size(); ++i)
  {
    drdt[forces_[i].first] += forces_[i].second;
  }
}

void excitor_dynamics::prepare_for_step()
{
  forces_ = generator_.generate();
}
