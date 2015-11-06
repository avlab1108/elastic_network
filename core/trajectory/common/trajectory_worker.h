#pragma once

#include <network.h>

#include <memory>

class network_dynamics;
class result_observer;

class trajectory_worker
{
protected:
  trajectory_worker(network& net, const network::node_positions_type& ininital_positions, const std::shared_ptr<network_dynamics>& dynamics);

  void set_result_observer(const std::shared_ptr<result_observer>& observer);

  virtual void run() = 0;

protected:
  network& net_;
  network::node_positions_type initial_positions_;
  std::shared_ptr<network_dynamics> dynamics_;
  std::shared_ptr<result_observer> observer_;
};
