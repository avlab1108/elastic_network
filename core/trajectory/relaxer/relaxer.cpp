#include "relaxer.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>

relaxer::relaxer(network& net, const network::node_positions_type& initial_positions, const long double step, const std::size_t max_time) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new network_dynamics(net, initial_positions))),
  step_(step),
  max_time_(max_time)
{
}

void relaxer::run()
{
  boost::numeric::odeint::runge_kutta_fehlberg78<network_dynamics::state_type> rkf78;
  boost::numeric::odeint::integrate_n_steps(rkf78, dynamics_, net_.get_node_positions(), 0.0l, step_, max_time_, observer_);
}
