#pragma once

#include <trajectory_worker.h>

#include <vector>

class excitor : public trajectory_worker
{
public:
  excitor(network& net, const network::node_positions_type& initial_positions, const double step, const std::size_t time, const double fs, const std::vector<std::size_t>& nodes = std::vector<std::size_t>());

  virtual void run() override;

private:
  const double step_;
  const std::size_t time_;
  const double fs_;
  const std::vector<std::size_t> nodes_;
};
