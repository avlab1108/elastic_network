#include "excitor.h"
#include "excitor_dynamics.h"
#include "force_generator.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>

excitor::excitor(network& net, const network::node_positions_type& initial_positions, const double step, const std::size_t time, const double fs, const std::vector<std::size_t>& nodes) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new excitor_dynamics(net, initial_positions, fs, nodes))),
  step_(step),
  time_(time),
  fs_(fs),
  nodes_(nodes)
{
}

void excitor::run()
{
  namespace odeint = boost::numeric::odeint;
  typedef odeint::runge_kutta_fehlberg78<network_dynamics::state_type, double, network_dynamics::state_type, double, odeint::openmp_range_algebra> error_stepper_type;
  typedef odeint::controlled_runge_kutta<error_stepper_type> controlled_stepper_type;
  controlled_stepper_type controlled_stepper;
  boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), 0.0, step_, time_, observer_);
}
