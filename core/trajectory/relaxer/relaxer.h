#pragma once

#include <network.h>

#include <trajectory_worker.h>

class relaxer : public trajectory_worker
{
public:
  relaxer(network& net, const network::node_positions_type& initial_positions, const std::size_t max_time);

  virtual void run();

private:
  const std::size_t max_time_;
};
