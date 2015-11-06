#include "relaxer.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>

relaxer::relaxer(network& net, const network::node_positions_type& initial_positions, const std::size_t max_time) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new network_dynamics(net, initial_positions))),
  max_time_(max_time)
{
}

void relaxer::run()
{
  boost::numeric::odeint::runge_kutta_fehlberg78<network_dynamics::state_type> rkf78;
  if(observer_)
  {
    boost::numeric::odeint::integrate_n_steps(rkf78, *dynamics_, net_.node_positions(), 0.0, 1.0, max_time_, *observer_);
  }
  else
  {
    boost::numeric::odeint::integrate_n_steps(rkf78, *dynamics_, net_.node_positions(), 0.0, 1.0, max_time_);
  }
}
