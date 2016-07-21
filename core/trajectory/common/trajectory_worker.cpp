#include "trajectory_worker.h"

trajectory_worker::trajectory_worker(network& net, const equilibrium_state_spec& equilibrium_state, const std::shared_ptr<network_dynamics>& dynamics) :
  net_(net),
  equilibrium_state_(equilibrium_state),
  dynamics_(dynamics),
  observer_(dynamics_)
{
}

void trajectory_worker::set_result_observer(const std::shared_ptr<result_observer>& observer)
{
  observer_.set_result_observer(observer);
}
