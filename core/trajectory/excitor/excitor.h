#pragma once

#include <network.h>
#include "excitor_dynamics.h"

#include <vector>

class excitor
{
public:
  excitor(network& net, const network::node_positions_type& initial_positions, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes = std::vector<std::size_t>());

  virtual void run();

private:
  network& net_;
  excitor_dynamics net_dynamics_;
  const double fs_;
  const std::size_t time_;
  const std::vector<std::size_t> nodes_;
};
