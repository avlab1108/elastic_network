#pragma once

#include <network.h>
#include <common_types.h>

#include <trajectory_worker.h>

class relaxer : public trajectory_worker
{
public:
  relaxer(network& net, const node_positions_type& initial_positions, const double step, const std::size_t max_time);

  virtual void run() override;

private:
  const double step_;
  const std::size_t max_time_;
};
