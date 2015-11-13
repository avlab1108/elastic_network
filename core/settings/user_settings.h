#pragma once

#include <network.h>

#include <cstdlib>
#include <vector>

class user_settings
{
public:
  user_settings();

  void set_network(const network& net);
  const network& network_() const;

  void set_excitation_time(const std::size_t time);
  const std::size_t excitation_time() const;

  void set_time_limit(const std::size_t limit);
  const std::size_t time_limit() const;

  void set_time_step(const double step);
  const double time_step() const;

  void set_fs(const double fs);
  const double fs() const;

  void set_simulations_count(const std::size_t simCount);
  const std::size_t simulations_count() const;

  void set_force_application_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& force_application_nodes() const;

  void set_visualization_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& visualization_nodes() const;

private:
  network net_;
  std::size_t excitationTime_;
  std::size_t timeLimit_;
  double time_step_;
  double fs_;
  std::size_t simulationsCount_;
  std::vector<std::size_t> forceApplicationNodes_;
  std::vector<std::size_t> visualizationNodes_;
};
