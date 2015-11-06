#pragma once

#include <trajectory_worker.h>

#include <vector>

class excitor : public trajectory_worker
{
public:
  excitor(network& net, const network::node_positions_type& initial_positions, const double fs, const std::size_t time, const std::vector<std::size_t>& nodes = std::vector<std::size_t>());

  virtual void run();

private:
  const double fs_;
  const std::size_t time_;
  const std::vector<std::size_t> nodes_;
};
