#pragma once

#include <network.h>
#include <network_dynamics.h>

#include <vector>

class relaxer
{
public:
  relaxer(network& net, const network::node_positions_type& initial_positions, const std::size_t max_time);

  virtual void run();

private:
  network& net_;
  network_dynamics net_dynamics_;
  const std::size_t max_time_;
};
