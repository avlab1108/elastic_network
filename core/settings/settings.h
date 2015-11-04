#pragma once

#include <network.h>

#include <cstdlib>
#include <vector>

class settings
{
public:
  settings();

  void setNetwork(const network& net);
  const network& network_() const;

  void setExcitationTime(const std::size_t time);
  const std::size_t excitationTime() const;

  void setTimeLimit(const std::size_t limit);
  const std::size_t timeLimit() const;

  void setFs(const double fs);
  const double fs() const;

  void setSimulationsCount(const std::size_t simCount);
  const std::size_t simutaionsCount() const;

  void setForceApplicationNodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& forceApplicationNodes() const;

  void setVisualizationNodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& visualizationNodes() const;

private:
  network net_;
  std::size_t excitationTime_;
  std::size_t timeLimit_;
  double fs_;
  std::size_t simulationsCount_;
  std::vector<std::size_t> forceApplicationNodes_;
  std::vector<std::size_t> visualizationNodes_;
};
