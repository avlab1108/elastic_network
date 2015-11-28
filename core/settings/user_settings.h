#pragma once

#include <network.h>

#include <cstdlib>
#include <vector>

#include <iostream>

class user_settings
{
public:
  user_settings();

  void set_network(const network& net);
  const network& get_network() const;

  void set_excitation_time(const std::size_t time);
  const std::size_t get_excitation_time() const;

  void set_time_limit(const std::size_t limit);
  const std::size_t get_time_limit() const;

  void set_time_step(const double step);
  const double get_time_step() const;

  void set_fs(const double fs);
  const double get_fs() const;

  void set_simulations_count(const std::size_t sim_count);
  const std::size_t get_simulations_count() const;

  void set_force_application_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& get_force_application_nodes() const;

  void set_visualization_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& get_visualization_nodes() const;

private:
  network net_;
  std::size_t excitation_time_;
  std::size_t time_limit_;
  double time_step_;
  double fs_;
  std::size_t simulations_count_;
  std::vector<std::size_t> force_application_nodes_;
  std::vector<std::size_t> visualization_nodes_;
};

std::ostream& operator<<(std::ostream& out, const user_settings& s);
