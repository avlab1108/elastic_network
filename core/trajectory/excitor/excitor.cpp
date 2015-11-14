#include "excitor.h"
#include "excitor_dynamics.h"
#include "force_generator.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>

excitor::excitor(network& net, const network::node_positions_type& initial_positions, const long double step, const std::size_t time, const long double fs, const std::vector<std::size_t>& nodes) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new excitor_dynamics(net, initial_positions, fs, nodes))),
  step_(step),
  time_(time),
  fs_(fs),
  nodes_(nodes)
{
}

void excitor::run()
{
  boost::numeric::odeint::runge_kutta_fehlberg78<network_dynamics::state_type> rkf78;
  boost::numeric::odeint::integrate_n_steps(rkf78, dynamics_, net_.get_node_positions(), 0.0l, step_, time_, observer_);
}
