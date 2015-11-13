#include "user_settings.h"

user_settings::user_settings() :
  excitationTime_(0),
  timeLimit_(0),
  fs_(0),
  simulationsCount_(0)
{
}

void user_settings::set_network(const network& net)
{
  net_ = net;
}

const network& user_settings::network_() const
{
  return net_;
}

void user_settings::set_excitation_time(const std::size_t time)
{
  excitationTime_ = time;
}

const std::size_t user_settings::excitation_time() const
{
  return excitationTime_;
}

void user_settings::set_time_limit(const std::size_t limit)
{
  timeLimit_ = limit;
}

const std::size_t user_settings::time_limit() const
{
  return timeLimit_;
}

void user_settings::set_time_step(const double step)
{
  time_step_ = step;
}

const double user_settings::time_step() const
{
  return time_step_;
}

void user_settings::set_fs(const double fs)
{
  fs_ = fs;
}

const double user_settings::fs() const
{
  return fs_;
}

void user_settings::set_simulations_count(const std::size_t simCount)
{
  simulationsCount_ = simCount;
}

const std::size_t user_settings::simulations_count() const
{
  return simulationsCount_;
}

void user_settings::set_force_application_nodes(const std::vector<std::size_t>& nodes)
{
  forceApplicationNodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::force_application_nodes() const
{
  return forceApplicationNodes_;
}

void user_settings::set_visualization_nodes(const std::vector<std::size_t>& nodes)
{
  visualizationNodes_ = nodes;
}

const std::vector<std::size_t>& user_settings::visualization_nodes() const
{
  return visualizationNodes_;
}
