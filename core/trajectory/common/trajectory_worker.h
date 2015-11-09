#pragma once

#include "result_observer.h"

#include <network.h>

#include <memory>

class network_dynamics;

class trajectory_worker
{
protected:
  trajectory_worker(network& net, const network::node_positions_type& ininital_positions, const std::shared_ptr<network_dynamics>& dynamics);

public:
  void set_result_observer(const std::shared_ptr<result_observer>& observer);

  virtual void run() = 0;

protected:
  network& net_;
  network::node_positions_type initial_positions_;
  network_dynamics_wrapper dynamics_;
  result_observer_wrapper observer_;
};
