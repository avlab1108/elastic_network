#include "settings.h"

settings::settings() :
  excitationTime_(0),
  timeLimit_(0),
  fs_(0),
  simulationsCount_(0)
{
}

void settings::set_network(const network& net)
{
  net_ = net;
}

const network& settings::network_() const
{
  return net_;
}

void settings::set_excitation_time(const std::size_t time)
{
  excitationTime_ = time;
}

const std::size_t settings::excitation_time() const
{
  return excitationTime_;
}

void settings::set_time_limit(const std::size_t limit)
{
  timeLimit_ = limit;
}

const std::size_t settings::time_limit() const
{
  return timeLimit_;
}

void settings::set_fs(const double fs)
{
  fs_ = fs;
}

const double settings::fs() const
{
  return fs_;
}

void settings::set_simulations_count(const std::size_t simCount)
{
  simulationsCount_ = simCount;
}

const std::size_t settings::simulations_count() const
{
  return simulationsCount_;
}

void settings::set_force_application_nodes(const std::vector<std::size_t>& nodes)
{
  forceApplicationNodes_ = nodes;
}

const std::vector<std::size_t>& settings::force_application_nodes() const
{
  return forceApplicationNodes_;
}

void settings::set_visualization_nodes(const std::vector<std::size_t>& nodes)
{
  visualizationNodes_ = nodes;
}

const std::vector<std::size_t>& settings::visualization_nodes() const
{
  return visualizationNodes_;
}
