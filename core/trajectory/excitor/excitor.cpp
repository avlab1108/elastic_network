#include "excitor.h"
#include "force_generator.h"
#include "result_observer.h"

#include <boost/numeric/odeint.hpp>

excitor::excitor(const network& net, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes) :
  net_(net),
  net_dynamics_(net_, force_generator(fs, nodes).generate()),
  fs_(fs),
  time_(time),
  nodes_(nodes)
{
}

void excitor::run()
{
  network_dynamics::state_type initial_state = net_.node_positions();
  boost::numeric::odeint::runge_kutta_fehlberg78<network_dynamics::state_type> rkf78;
  result_observer writer(std::cout);
  boost::numeric::odeint::integrate_n_steps(rkf78, net_dynamics_, initial_state, 0.0, 1.0, time_, writer);
}
