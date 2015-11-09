#include "excitor_dynamics.h"

excitor_dynamics::excitor_dynamics(const network& net, const network::node_positions_type& initial_positions, const double fs, const std::vector<std::size_t>& nodes) :
  network_dynamics(net, initial_positions),
  fs_(fs),
  nodes_(nodes),
  generator_(fs_, nodes_)
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
