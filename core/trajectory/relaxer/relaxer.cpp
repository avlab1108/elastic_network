#include "relaxer.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>

relaxer::relaxer(network& net, const network::node_positions_type& initial_positions, const double step, const std::size_t max_time) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new network_dynamics(net, initial_positions))),
  step_(step),
  max_time_(max_time)
{
}

void relaxer::run()
{
  namespace odeint = boost::numeric::odeint;
  typedef odeint::runge_kutta_fehlberg78<network_dynamics::state_type, double, network_dynamics::state_type, double, odeint::openmp_range_algebra> error_stepper_type;
  typedef odeint::controlled_runge_kutta<error_stepper_type> controlled_stepper_type;
  controlled_stepper_type controlled_stepper;
  boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), 0.0, step_, max_time_, observer_);
}
