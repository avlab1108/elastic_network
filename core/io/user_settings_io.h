/**
 * @file user_settings_io.h
 * @brief This file contains @ref user_settings_io class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <network.h>
#include <user_settings.h>

#include <yaml-cpp/yaml.h>

/**
 * @namespace usc
 * @brief Contains key names for settings in user settings file.
 *
 * @note usc disambiguates as user settings constants.
 */
namespace usc
{
/// Summary magnitude of forces.
const std::string fs = "Fs";
/// Nodes of network.
const std::string nodes = "nodes";
/// Links of network.
const std::string links = "links";
/// Time of excitation (preparation) of network.
const std::string excitation_time = "timeIni";
/// Number of repetitions.
const std::string simulations_count = "runNum";
/// Force application nodes.
const std::string force_application_nodes = "activeNodes";
/// Specify whether excitation forces are dynamic/static.
const std::string forces_dynamic = "forcesDynamic";
/// Nodes for trajectory construction.
const std::string visualization_nodes = "visualizationNodes";
/// Network file name.
const std::string network_file_path = "networkFile";
/// Excitation time step.
const std::string excitation_time_step = "excitationTimeStep";
/// Equilibrium state of network.
const std::string equilibrium_state = "equilibriumState";
/// Equilibrium distances between nodes of network.
const std::string equilibrium_distances = "distances";

/**
 * @namespace rtss
 * @brief Relaxation time specification.
 * @note rtss stands for relaxation time step specification.
 */
namespace rtss
{
/// Self name.
const std::string self = "relaxationTimeStepSpec";
/// Initial nitial step.
const std::string initial_step = "initialStep";
/// Time delta.
const std::string time_delta = "timeDelta";
/// Multiplication coefficient.
const std::string coefficient = "coefficient";
}

}

namespace YAML
{
class Node;
}

/**
 * @class user_settings_io
 * @brief Controls i/o of user settings.
 */
class user_settings_io
{
public:
  /**
   * @brief Constructs @a user_settings_io object.
   */
  user_settings_io();

  /**
   * @brief Imports user settings from provided file.
   * @param file_path User settings file name.
   *
   * Import is based on the keys described in @ref usc.
   */
  void import_settings(const std::string& file_path);
  /**
   * @brief Exports user settings into provided directory.
   * @param output_dir Directory name.
   *
   * Export is based on the keys described in @ref usc.
   */
  void export_settings(const std::string& output_dir);

  /**
   * @brief Returns settings.
   * @return User settings.
   */
  const user_settings& get_settings() const;
  /**
   * @brief Returns settings with modification permissions.
   * @return User settings.
   */
  user_settings& get_settings();
  
private:
  /**
   * @brief Checks input YAML tree for existence/correctness of all necessary settings.
   * @param node YAML node.
   */
  void check_input_validity(const YAML::Node& node) const;
  /**
   * @brief Imports network from provided @ref node.
   * @param node YAML node to read network from.
   *
   * Tries to read network from path, provided with usc::network_file_path key.
   */
  void import_network_from_external_file(const YAML::Node& node);
  /**
   * @brief Imports equilibrium state specification from @ref node.
   * @param node YAML node to read equilibrium state from.
   */
  void import_equilibrium_state_spec(const YAML::Node& node);
  /**
   * @brief Reads network from provided YAML tree node.
   * @param node YAML node for network.
   * @return Read network.
   */
  network read_network_from_yaml(const YAML::Node& node);
  /**
   * @brief Reads network from provided YAML file.
   * @param file_path Network file name.
   * @return Read network.
   */
  network read_network_from_yaml_file(const std::string& file_path);

  /**
   * @brief Reads equilibrium state specification from provided YAML tree node.
   * @param node YAML node for equilibrium state specification.
   * @return Read equilibrium state specification.
   */
  equilibrium_state_spec read_equilibrium_state_from_yaml(const YAML::Node& node);
  /**
   * @brief Reads equilibrium state specification from provided YAML file.
   * @param file_path Equilibrium state file name.
   * @return Read equilibrium state specification.
   */
  equilibrium_state_spec read_equilibrium_state_from_yaml_file(const std::string& file_path);

private:
  /// User settings.
  user_settings settings_;
  /// User settings file name.
  std::string settings_file_name_;
};
