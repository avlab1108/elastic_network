#include "settings.h"

settings::settings() :
  excitationTime_(0),
  timeLimit_(0),
  fs_(0),
  simulationsCount_(0)
{
}

void settings::setNetwork(const network& net)
{
  net_ = net;
}

const network& settings::network_() const
{
  return net_;
}

void settings::setExcitationTime(const std::size_t time)
{
  excitationTime_ = time;
}

const std::size_t settings::excitationTime() const
{
  return excitationTime_;
}

void settings::setTimeLimit(const std::size_t limit)
{
  timeLimit_ = limit;
}

const std::size_t settings::timeLimit() const
{
  return timeLimit_;
}

void settings::setFs(const double fs)
{
  fs_ = fs;
}

const double settings::fs() const
{
  return fs_;
}

void settings::setSimulationsCount(const std::size_t simCount)
{
  simulationsCount_ = simCount;
}

const std::size_t settings::simutaionsCount() const
{
  return simulationsCount_;
}

void settings::setForceApplicationNodes(const std::vector<std::size_t>& nodes)
{
  forceApplicationNodes_ = nodes;
}

const std::vector<std::size_t>& settings::forceApplicationNodes() const
{
  return forceApplicationNodes_;
}

void settings::setVisualizationNodes(const std::vector<std::size_t>& nodes)
{
  visualizationNodes_ = nodes;
}

const std::vector<std::size_t>& settings::visualizationNodes() const
{
  return visualizationNodes_;
}
