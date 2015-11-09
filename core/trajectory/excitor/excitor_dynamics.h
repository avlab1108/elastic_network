#pragma once

#include "force_generator.h"

#include <point.h>
#include <network_dynamics.h>

class excitor_dynamics : public network_dynamics
{
public:
  typedef std::vector<std::pair<std::size_t, point_type>> forces_type;

public:
  excitor_dynamics(const network& net, const network::node_positions_type& initial_positions, const double fs, const std::vector<std::size_t>& nodes);
  virtual void calculate(const state_type& r, state_type& drdt, const double t) override;
  virtual void prepare_for_step() override;

private:
  const double fs_;
  const std::vector<std::size_t> nodes_;
  forces_type forces_;
  force_generator generator_;
};
