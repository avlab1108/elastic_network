#include "excitor.h"
#include "excitor_dynamics.h"
#include "force_generator.h"

#include <result_observer.h>

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>

namespace
{

std::vector<std::size_t> all_nodes(const network& net)
{
  std::vector<std::size_t> res(net.get_size());
  for(std::size_t i = 0; i < net.get_size(); ++i)
  {
    res.push_back(i);
  }
  return res;
}

forces_spec update_spec_for_net(const forces_spec& fspec, const network& net)
{
  std::vector<std::size_t> nodes = fspec.nodes;
  if(nodes.empty())
  {
    nodes = all_nodes(net);
  }
  return forces_spec(fspec.fs, nodes, fspec.dynamic);
}

}

excitor::excitor(network& net, const node_positions_type& initial_positions, const double step, const std::size_t time, const forces_spec& fspec) :
  trajectory_worker(net, initial_positions, std::make_shared<excitor_dynamics>(net, initial_positions, update_spec_for_net(fspec, net))),
  step_(step),
  time_(time)
{
}

void excitor::run()
{
  namespace odeint = boost::numeric::odeint;
  typedef odeint::runge_kutta_dopri5<state_type, double, state_type, double, odeint::openmp_range_algebra> error_stepper_type;
  typedef odeint::controlled_runge_kutta<error_stepper_type> controlled_stepper_type;
  controlled_stepper_type controlled_stepper;
  boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), 0.0, step_, time_, observer_);
}
