#include "result_observer.h"

#include <logging.h>
#include <utils.h>

#include <iomanip>

stream_dumper::stream_dumper(format_type format, std::ostream& out) :
  format_(format),
  out_(out)
{
  if(!out_.good())
  {
    LOG(logger::error, std::string("Invalid stream handle provided. Output will not be available."));
  }
}

void stream_dumper::process(const state_type& r, const double t)
{
  switch(format_)
  {
    case format_type::gnuplot:
      format_for_gnuplot(r, t);
      break;
    case format_type::raw:
      format_for_raw(r, t);
      break;
    default:
      break;
  }
}

void stream_dumper::format_for_raw(const state_type& r, const double t)
{
  std::lock_guard<std::mutex> lock(out_mutex_);
  for(std::size_t i = 0; i < r.size(); ++i)
  {
    out_ << r[i] << std::endl;
  }
  out_ << std::endl;
}

void stream_dumper::format_for_gnuplot(const state_type& r, const double t)
{
  std::lock_guard<std::mutex> lock(out_mutex_);
  for(std::size_t i = 0; i < r.size(); ++i)
  {
    out_ << std::setw(15) << std::left << r[i][0] << std::setw(15) << std::left << r[i][1] << std::setw(15) << r[i][2];
    out_ << std::endl;
  }
  out_ << '\n' << std::endl;
}

file_dumper::file_dumper(const std::string& filepath, stream_dumper::format_type format) :
  out_(filepath),
  dumper_(format, out_)
{
  if(!out_.is_open())
  {
    LOG(logger::error, std::string("Failed to open output file \"") + filepath + "\". Output will not be available.");
  }
}

file_dumper::~file_dumper()
{
  if(out_.is_open())
  {
    out_.close();
  }
}

void file_dumper::process(const state_type& r, const double t)
{
  dumper_.process(r, t);
}

trajectory_dumper::trajectory_dumper(std::ostream& out, const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const std::size_t step) :
  out_(out),
  initial_positions_(initial_positions),
  nodes_(nodes),
  step_(step)
{
  if(!out_.good())
  {
    LOG(logger::error, std::string("Invalid stream handle provided. Output will not be available."));
  }
}

void trajectory_dumper::process(const state_type& r, const double t)
{
  static std::size_t counter = 0;
  if(0 == counter++ % step_)
  {
    std::size_t i1 = nodes_[0];
    std::size_t i2 = nodes_[1];
    std::size_t i3 = nodes_[2];

    double current_dist = utils::distance(r[i1], r[i2]);
    double initial_dist = utils::distance(initial_positions_[i1], initial_positions_[i2]);
    double val1 = (current_dist-initial_dist)/initial_dist;

    current_dist = utils::distance(r[i1], r[i3]);
    initial_dist = utils::distance(initial_positions_[i1], initial_positions_[i3]);
    double val2 = (current_dist-initial_dist)/initial_dist;

    current_dist = utils::distance(r[i2], r[i3]);
    initial_dist = utils::distance(initial_positions_[i2], initial_positions_[i3]);
    double val3 = (current_dist-initial_dist)/initial_dist;

    std::lock_guard<std::mutex> lock(out_mutex_);
    out_ << val1 << " " << val2 << " " << val3 << std::endl;
  }
}

stability_checker::stability_checker(const node_positions_type& initial_positions, const node_chooser::node_numbers_type& nodes, const stabilization_spec stab_spec) :
  initial_positions_(initial_positions),
  nodes_(nodes),
  stabilization_steps_(0),
  stab_spec_(stab_spec)
{
  std::size_t i1 = nodes_[0];
  std::size_t i2 = nodes_[1];
  std::size_t i3 = nodes_[2];
  previous_dist1_ = utils::distance(initial_positions_[i1], initial_positions_[i2]);
  previous_dist2_ = utils::distance(initial_positions_[i1], initial_positions_[i3]);
  previous_dist3_ = utils::distance(initial_positions_[i2], initial_positions_[i3]);
}

void stability_checker::process(const state_type& r, const double t)
{
  std::size_t i1 = nodes_[0];
  std::size_t i2 = nodes_[1];
  std::size_t i3 = nodes_[2];
  const double& epsilon = stab_spec_.epsilon;
  if(utils::distance(initial_positions_[i1], r[i1]) < epsilon &&
    utils::distance(initial_positions_[i2], r[i2]) < epsilon &&
    utils::distance(initial_positions_[i3], r[i3]) < epsilon)
  {
    throw std::exception();
  }

  double current_dist1 = utils::distance(r[i1], r[i2]);
  double current_dist2 = utils::distance(r[i1], r[i3]);
  double current_dist3 = utils::distance(r[i2], r[i3]);
  if(std::fabs(current_dist1 - previous_dist1_) < epsilon &&
    std::fabs(current_dist2 - previous_dist2_) < epsilon &&
    std::fabs(current_dist3 - previous_dist3_) < epsilon)
  {
    ++stabilization_steps_;
  }
  else
  {
    stabilization_steps_ = 0;
  }
  previous_dist1_ = current_dist1;
  previous_dist2_ = current_dist2;
  previous_dist3_ = current_dist3;
  if(stab_spec_.step_count == stabilization_steps_)
  {
    throw std::exception();
  }
}

composite_result_observer::composite_result_observer()
{
}

void composite_result_observer::process(const state_type& r, const double t)
{
  for(auto it = observers_.begin(); it != observers_.end(); ++it)
  {
    (*it)->process(r, t);
  }
}

void composite_result_observer::add_result_observer(const std::shared_ptr<result_observer>& observer)
{
  observers_.push_back(observer);
}

result_observer_wrapper::result_observer_wrapper(const network_dynamics_wrapper& dynamics) :
  dynamics_(dynamics)
{
}

void result_observer_wrapper::operator()(const state_type& r, const double t)
{
  dynamics_.prepare_for_step();
  if(observer_)
  {
    observer_->process(r, t);
  }
}

void result_observer_wrapper::set_result_observer(const std::shared_ptr<result_observer>& observer)
{
  observer_ = observer;
}
