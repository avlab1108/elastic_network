#pragma once

#include <trajectory_worker.h>

#include <vector>

class excitor : public trajectory_worker
{
public:
  excitor(network& net, const node_positions_type& initial_positions, const double step, const std::size_t time, const forces_spec& fspec);

  virtual void run() override;

private:
  const double step_;
  const std::size_t time_;
};
