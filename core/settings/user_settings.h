/**
 * @file user_settings.h
 * @brief This file contains @ref user_settings class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <network.h>

#include <boost/optional.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>

/**
 * @class user_settings
 * @brief User settings.
 *
 * Contains parameters, which describe settings for executing necessary tasks.
 */
class user_settings
{
public:
  /**
   * @brief Constructs user settings object.
   */
  user_settings();

  /**
   * @brief Sets network.
   * @param net Network.
   */
  void set_network(const network& net);
  /**
   * @brief Returns network.
   * @return Network.
   */
  const network& get_network() const;

  /**
   * @brief Sets excitation time.
   * @param time Excitation time.
   */
  void set_excitation_time(const std::size_t time);
  /**
   * @brief Returns excitation time.
   * @return Excitation time.
   */
  std::size_t get_excitation_time() const;

  /**
   * @brief Sets excitation time step.
   * @param step Excitation time step.
   */
  void set_excitation_time_step(const double step);
  /**
   * @brief Returns excitation time step.
   * @return Excitation time step.
   */
  double get_excitation_time_step() const;

  /**
   * @brief Sets relaxation time step specification.
   * @param step_spec Step specification.
   */
  void set_relaxation_time_step_spec(const relaxation_time_step_spec& step_spec);
  /**
   * @brief Returns relaxation time step specification.
   * @return Relaxation time step specification.
   */
  const relaxation_time_step_spec& get_relaxation_time_step_spec() const;

  /**
   * @brief Sets summary magnitude of forces.
   * @param fs Summary magnitude of forces.
   */
  void set_fs(const double fs);
  /**
   * @brief Returns summary magnitude of forces.
   * @return Summary magnitude of forces.
   */
  double get_fs() const;

  /**
   * @brief Sets number of trajectory generations.
   * @param sim_count Number of trajectories.
   */
  void set_simulations_count(const std::size_t sim_count);
  /**
   * @brief Returns number of trajectory generations.
   * @return Number of generations.
   */
  std::size_t get_simulations_count() const;

  /**
   * @brief Sets nodes for visualization during trajectory generation.
   * @param nodes Nodes for visualization.
   */
  void set_visualization_nodes(const std::vector<std::size_t>& nodes);
  /**
   * @brief Returns nodes for visualization during trajectory generation.
   * @return Nodes for visualization.
   */
  const std::vector<std::size_t>& get_visualization_nodes() const;

  /**
   * @brief Sets nodes for force application during exctitation process.
   * @param nodes Force application nodes.
   */
  void set_force_application_nodes(const std::vector<std::size_t>& nodes);
  /**
   * @brief Returns nodes for force application during excitation process.
   * @return Force application nodes.
   */
  const std::vector<std::size_t>& get_force_application_nodes() const;

  /**
   * @brief Sets flag indicating whether excitation forces are dynamic.
   * @param dynamic True for dynamic forces, false for static forces.
   */
  void set_forces_dynamic(const bool dynamic);
  /**
   * @brief Returns flag indicating whether excitation forces are dynamic.
   * @return True if excitation forces are dynamic, false otherwise.
   */
  bool get_forces_dynamic() const;

  /**
   * @brief Sets node positions for network.
   * @param node_positions Node positions.
   */
  void set_node_positions(const node_positions_t& node_positions);
  /**
   * @brief Returns node positions (if set).
   * @return Optional node positions.
   */
  const boost::optional<node_positions_t>& get_node_positions() const;

  /**
   * @brief Sets cutoff distance for network.
   * @param l0 Cutoff distance.
   */
  void set_cutoff_distance(const double l0);
  /**
   * @brief Returns cutoff distance (if set).
   * @return Optional cutoff distance.
   */
  const boost::optional<double>& get_cutoff_distance() const;

  /**
   * @brief Sets network links.
   * @param links Network links.
   */
  void set_links(const std::vector<std::pair<std::size_t, std::size_t>>& links);
  /**
   * @brief Returns network links (if set).
   * @return Optional network links.
   */
  const boost::optional<std::vector<std::pair<std::size_t, std::size_t>>>& get_links() const;

  /**
   * @brief Sets network file path.
   * @param path Network file path.
   */
  void set_network_file_path(const std::string& path);
  /**
   * @brief Returns network file path (if set).
   * @return Optional network file path.
   */
  const boost::optional<std::string>& get_network_file_path() const;

	/**
	 * @brief Sets equilibrium state specification.
	 * @param state Equilibrium state specification.
	 */
	void set_equilibrium_state_spec(const equilibrium_state_spec& state);
	/**
	 * @brief Returns equilibrium state specification (if set).
	 * @return Optional equilibrium state specification.
	 */
	const boost::optional<equilibrium_state_spec>& get_equilibrium_state_spec() const;

private:
  /**
   * @brief Required parameters
   * @{
   */
  /// Network.
  network net_;
  /// Excitation time step.
  double excitation_time_step_;
  /// Excitation time.
  std::size_t excitation_time_;
  /// Relaxation time step spec.
  relaxation_time_step_spec relaxation_time_step_spec_;
  /// Summary magnitude of random forces.
  double fs_;
  /// Simulation count.
  std::size_t simulations_count_;
  /// Nodes for visualization.
  std::vector<std::size_t> visualization_nodes_;
  /// Force application nodes.
  std::vector<std::size_t> force_application_nodes_;
  /// Dynamic/static forces.
  bool forces_dynamic_;
  /**
   * @}
   */
  /**
   * @brief Optional parameters.
   * Some of these parameters has some mutual conditions and in some cases 
   * they can become required.
   * For example - Nodes and Network file path are mutual exclusive.
   * If Nodes is defined, Links or Cutoff distance should also be defined
   * (so one of them becomes required).
   * @{
   */
  /// Nodes.
  boost::optional<node_positions_t> node_positions_;
  /// Links.
  boost::optional<links_t> links_;
  /// Cutoff distance.
  boost::optional<double> cutoff_distance_;
  /// Network file path.
  boost::optional<std::string> network_file_path_;
	/// Equilibrium state specification.
	boost::optional<equilibrium_state_spec> equilibrium_state_spec_;
  /**
   * @}
   */
};

std::ostream& operator<<(std::ostream& out, const user_settings& s);
