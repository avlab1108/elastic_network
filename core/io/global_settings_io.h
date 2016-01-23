/**
 * @file global_settings_io.h
 * @brief This file contains @ref global_settings_io class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <global_settings.h>

#include <yaml-cpp/yaml.h>

/**
 * @namespace gsc
 * @brief Contains key names for settings in global settings file.
 *
 * @note gsc disambiguates as global settings constants.
 */
namespace gsc
{
/// Results directory prefix.
const std::string results_dir = "resultsDir";
/// Single generation (trajectory) directory prefix.
const std::string generation_dir = "generationDir";
/// Excitation file name.
const std::string excitation_file_name = "excitationFileName";
/// Relaxation file name.
const std::string relaxation_file_name = "relaxationFileName";
/// Trajectory file name.
const std::string trajectory_file_name = "trajectoryFileName";
/// Eigenvalues and eigenvectors file name.
const std::string eigens_file_name = "eigensFileName";
/// Node file name.
const std::string nodes_file_name = "nodesFileName";
/// Enable/disable additional data dump (excitation and relaxation files).
const std::string dump_data = "dumpData";
/// Dump step for additional data dump.
const std::string dump_step = "dumpStep";
/// Time limit specification for relaxation process.
const std::string time_limit = "timeLimit";
/// Specify whether excitation forces are dynamic/static.
const std::string forces_dynamic = "forcesDynamic";
}

namespace YAML
{
class Node;
}

/**
 * @class global_settings_io
 * @brief Controls i/o of global settings.
 */
class global_settings_io
{
public:
  /**
   * @brief Constructs @a global_settings_io object.
   */
  global_settings_io();

  /**
   * @brief Imports global settings from provided file.
   * @param file_path Global settings file name.
   *
   * Import is based on the keys described in @namespace constants.
   */
  void import_settings(const std::string& file_path);
  /**
   * @brief Exports global settings into provided directory.
   * @param output_dir Directory name.
   *
   * Export is based on the keys described in @namespace constants.
   */
  void export_settings(const std::string& output_dir);

  /**
   * @brief Returns settings.
   * @return Global settings.
   */
  const global_settings& get_settings() const;

private:
  /**
   * @brief Checks input YAML tree for existence/correctness of all necessary settings.
   * @param node YAML node.
   */
  void check_input_validity(const YAML::Node& node);

private:
  /// Global settings.
  global_settings settings_;
  /// Global settings file name.
  std::string settings_file_name_;
};
