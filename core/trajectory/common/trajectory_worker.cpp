#include "trajectory_worker.h"

trajectory_worker::trajectory_worker(network& net, const network::node_positions_type& initial_positions, const std::shared_ptr<network_dynamics>& dynamics) :
  net_(net),
  initial_positions_(initial_positions),
  dynamics_(dynamics)
{
}

void trajectory_worker::set_result_observer(const std::shared_ptr<result_observer>& observer)
{
  observer_ = observer;
}
