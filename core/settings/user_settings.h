#pragma once

#include <network.h>

#include <cstdlib>
#include <vector>

#include <boost/optional.hpp>

#include <iostream>

class user_settings
{
public:
  user_settings();

  void set_network(const network& net);
  const network& get_network() const;

  void set_excitation_time(const std::size_t time);
  const std::size_t get_excitation_time() const;

  void set_time_step(const double step);
  const double get_time_step() const;

  void set_fs(const double fs);
  const double get_fs() const;

  void set_simulations_count(const std::size_t sim_count);
  const std::size_t get_simulations_count() const;

  void set_visualization_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& get_visualization_nodes() const;

  void set_force_application_nodes(const std::vector<std::size_t>& nodes);
  const std::vector<std::size_t>& get_force_application_nodes() const;

  void set_nodes(const std::vector<std::size_t>& nodes);
  const boost::optional<std::vector<std::size_t>>& get_nodes() const;

  void set_cutoff_distance(const double l0);
  const boost::optional<double>& get_cutoff_distance() const;

  void set_links(const std::vector<std::pair<std::size_t, std::size_t>>& links);
  const boost::optional<std::vector<std::pair<std::size_t, std::size_t>>>& get_links() const;

  void set_network_file_path(const std::string& path);
  const boost::optional<std::string>& get_network_file_path() const;

private:
  /**
   * Required parameters
   * @{
   */
  /// Network.
  network net_;
  /// Time step.
  double time_step_;
  /// Excitation time.
  std::size_t excitation_time_;
  /// Summary magnitude of random forces.
  double fs_;
  /// Simulation count.
  std::size_t simulations_count_;
  /// Nodes for visualization.
  std::vector<std::size_t> visualization_nodes_;
  /// Force application nodes.
  std::vector<std::size_t> force_application_nodes_;
  /**
   * @}
   */
  /**
   * Optional parameters.
   * Some of these parameters has some mutual conditions and in some cases 
   * they can become required.
   * For example - Nodes and Network file path are mutual exclusive.
   * If Nodes is defined, Links or Cutoff distance should also be defined
   * (so one of them becomes required).
   * @{
   */
  /// Nodes.
  boost::optional<std::vector<std::size_t>> nodes_;
  /// Links.
  boost::optional<std::vector<std::pair<std::size_t, std::size_t>>> links_;
  /// Cutoff distance.
  boost::optional<double> cutoff_distance_;
  /// Network file path.
  boost::optional<std::string> network_file_path_;
  /**
   * @}
   */
};

std::ostream& operator<<(std::ostream& out, const user_settings& s);
