#include "relaxer.h"

#include <result_observer.h>
#include <logging.h>

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>

relaxer::relaxer(network& net, const node_positions_type& initial_positions, const relaxation_time_step_spec& step_spec, const std::size_t max_time) :
  trajectory_worker(net, initial_positions, std::make_shared<network_dynamics>(net, initial_positions)),
  step_spec_(step_spec),
  max_time_(max_time)
{
}

void relaxer::run()
{
  namespace odeint = boost::numeric::odeint;
  typedef odeint::runge_kutta_dopri5<state_type, double, state_type, double, odeint::openmp_range_algebra> error_stepper_type;
  typedef odeint::controlled_runge_kutta<error_stepper_type> controlled_stepper_type;
  controlled_stepper_type controlled_stepper;
  try
  {
    if(1 >= step_spec_.time_delta || std::abs(1.0 - step_spec_.coefficient) < 1e-9)
    {
      // if time delta is less than or equal to 1 or multiply coefficient is 1.0, then reset to default scheme without time step change.
      boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), 0.0, step_spec_.initial_step, max_time_, observer_);
    }
    else
    {
      // else divide overall time of integration into time_delta parts and integrate with appropriate step.
      std::size_t step_delta = step_spec_.time_delta;
      std::size_t num_chunks = max_time_ / step_delta;
      double start = 0.0;
      for(std::size_t i = 0; i < num_chunks; ++i)
      {
        double current_step = step_spec_.initial_step * std::pow(step_spec_.coefficient, i);
        boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), start, current_step, step_delta, observer_);
        start += step_delta * current_step;
      }
      if(0 != max_time_ % step_delta)
      {
        double current_step = step_spec_.initial_step * std::pow(step_spec_.coefficient, num_chunks);
        boost::numeric::odeint::integrate_n_steps(controlled_stepper, dynamics_, net_.get_node_positions(), start, current_step, step_delta, observer_);
      }
    }
    LOG(logger::warning, "Relaxation was stopped as the relaxation time exceeded maximal allowed time.");
  }
  catch(const std::exception&)
  {
    LOG(logger::info, "Relaxation finished.");
  }
}
