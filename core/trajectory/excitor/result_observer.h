#pragma once

#include <network_dynamics.h>

#include <iostream>

class result_observer
{
public:
  typedef network_dynamics::state_type state_type;

  result_observer(std::ostream& out);

  void operator()(const state_type& x, const double t) const;

private:
  std::ostream& out_;
};
