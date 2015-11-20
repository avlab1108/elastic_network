#pragma once

#include "network.h"
#include "point.h"

#include <memory>
#include <vector>

class network_dynamics
{
public:
  typedef std::vector<point_type> state_type;

public:
  network_dynamics(const network& net, const network::node_positions_type& initial_positions);
  virtual void calculate(const state_type& r, state_type& drdt, const double t);
  virtual void prepare_for_step();

private:
  network net_;
  network::node_positions_type initial_positions_;
  std::vector<std::vector<double>> initial_distances_;
};

class network_dynamics_wrapper
{
public:
  typedef network_dynamics::state_type state_type;

public:
  network_dynamics_wrapper(const std::shared_ptr<network_dynamics>& dynamics);
  void operator() (const state_type& r, state_type& drdt, const double t);

  void prepare_for_step();

private:
  std::shared_ptr<network_dynamics> dynamics_;
};

typedef std::shared_ptr<network_dynamics> network_dynamics_ptr;
