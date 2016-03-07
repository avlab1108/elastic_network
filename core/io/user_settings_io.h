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
/// Cutoff distance for network links.
const std::string l0 = "L0";
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
   * @brief Imports network from provided external file.
   * @param file_path Network file name.
   *
   * Based on @a file_path extension, this function delegates reading of real network to one of the read_network_from_* methods.
   * \n Following formats are supported (with according read function):
   * \n .yml  -> @ref read_network_from_yaml_file
   * \n .yaml -> @ref read_network_from_yaml_file
   * \n .csv  -> @ref read_network_from_csv_file
   * \n .dat  -> @ref read_network_from_csv_file
   * \n .txt  -> @ref read_network_from_csv_file
   */
  void import_network_from_external_file(const std::string& file_path);
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
   * @brief Reads network from provided CSV (Comma Separated Values) file.
   * @param file_path Network file name.
   * @return Read network.
   *
   * @note CSV is a common name for raw textual files, where data is separated with some delimiter (not necessarily commas).
   */
  network read_network_from_csv_file(const std::string& file_path);

private:
  /// User settings.
  user_settings settings_;
  /// User settings file name.
  std::string settings_file_name_;
  /// Network file name.
  std::string network_file_name_;
};
