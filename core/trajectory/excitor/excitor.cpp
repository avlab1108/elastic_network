#include "excitor.h"
#include "excitor_dynamics.h"
#include "force_generator.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>

excitor::excitor(network& net, const network::node_positions_type& initial_positions, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes) :
  trajectory_worker(net, initial_positions, network_dynamics_ptr(new excitor_dynamics(net, initial_positions, force_generator(fs, nodes).generate()))),
  fs_(fs),
  time_(time),
  nodes_(nodes)
{
}

void excitor::run()
{
  boost::numeric::odeint::runge_kutta_fehlberg78<network_dynamics::state_type> rkf78;
  if(observer_)
  {
    boost::numeric::odeint::integrate_n_steps(rkf78, *dynamics_, net_.node_positions(), 0.0, 1.0, time_, *observer_);
  }
  else
  {
    boost::numeric::odeint::integrate_n_steps(rkf78, *dynamics_, net_.node_positions(), 0.0, 1.0, time_);
  }
}
