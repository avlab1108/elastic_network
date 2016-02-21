/**
 * @file global_settings.h
 * @brief This file contains @ref global_settings class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <common_types.h>

#include <string>

/**
 * @class global_settings
 * @brief Global settings.
 *
 * Contains parameters, which describe various global settings, such as output file/folder names, output control flags, etc.
 */
class global_settings
{
public:
  /**
   * @brief Constructs global settings object.
   */
  global_settings();

  /**
   * @brief Sets output results directory.
   * @param dir Output directory name.
   */
  void set_results_dir(const std::string& dir);
  /**
   * @brief Returns output results directory.
   * @return Output directory name.
   */
  const std::string& get_results_dir() const;

  /**
   * @brief Sets directory name for single generation output.
   * @param dir Output directory name.
   */
  void set_generation_dir(const std::string& dir);
  /**
   * @brief Returns directory name for single generation output.
   * @return Output directory name.
   */
  const std::string& get_generation_dir() const;

  /**
   * @brief Sets excitation output file name.
   * @param file_name Output file name.
   */
  void set_excitation_file_name(const std::string& file_name);
  /**
   * @brief Returns excitation output file name.
   * @return Output file name.
   */
  const std::string& get_excitation_file_name() const;

  /**
   * @brief Sets relaxation output file name.
   * @param file_name Output file name.
   */
  void set_relaxation_file_name(const std::string& file_name);
  /**
   * @brief Returns relaxation output file name.
   * @return Output file name.
   */
  const std::string& get_relaxation_file_name() const;

  /**
   * @brief Sets trajectory output file name.
   * @param file_name Output file name.
   */
  void set_trajectory_file_name(const std::string& file_name);
  /**
   * @brief Returns trajectory output file name.
   * @return Output file name.
   */
  const std::string& get_trajectory_file_name() const;

  /**
   * @brief Sets eigenvalues/eigenvectors output file name.
   * @param file_name Output file name.
   */
  void set_eigens_file_name(const std::string& file_name);
  /**
   * @brief Returns eigenvalues/eigenvectors output file name.
   * @return Output file name.
   */
  const std::string& get_eigens_file_name() const;

  /**
   * @brief Sets optimal nodes output file name.
   * @param file_name Output file name.
   */
  void set_nodes_file_name(const std::string& file_name);
  /**
   * @brief Returns optimal nodes output file name.
   * @return Output file name.
   */
  const std::string& get_nodes_file_name() const;

  /**
   * @brief Sets flag indicating whether to dump excitation/relaxation data.
   * @param dump True to dump, false to not.
   */
  void set_dump_data(const bool dump);
  /**
   * @brief Returns flag indicating whether dump of excitation/relaxation data is enabled.
   * @return True if dump is enabled, false otherwise.
   */
  const bool get_dump_data() const;

  /**
   * @brief Sets dump step for excitation/relaxation data.
   * @param step Dump step.
   */
  void set_dump_step(const std::size_t step);
  /**
   * @brief Returns dump step for excitation/relaxation data.
   * @return Dump step.
   */
  const std::size_t get_dump_step() const;

  /**
   * @brief Sets time limit for relaxation process.
   * @param limit Limit value.
   */
  void set_time_limit(const std::size_t limit);
  /**
   * @brief Returns time limit for relaxation process.
   * @return Limit value.
   */
  const std::size_t get_time_limit() const;

  /**
   * @brief Sets stabilization specification for stabilization determination.
   * @param spec Stabilization specification.
   */
  void set_stabilization_spec(const stabilization_spec& spec);
  /**
   * @brief Returns stabilization specification used for stabilization determination.
   * @return Stabilization spec.
   */
  const stabilization_spec& get_stabilization_spec() const;

private:
  /// Output results directory.
  std::string results_dir_;
  /// Single generation output directory.
  std::string generation_dir_;
  /// Excitation file name.
  std::string excitation_file_name_;
  /// Relaxation file name.
  std::string relaxation_file_name_;
  /// Trajectory file name.
  std::string trajectory_file_name_;
  /// Eigenvalues and eigenvectors file name.
  std::string eigens_file_name_;
  /// Optimal nodes file name.
  std::string nodes_file_name_;
  /// Dump or not data.
  bool dump_data_;
  /// Dump step.
  std::size_t dump_step_;
  /// Relaxation time limit.
  std::size_t time_limit_;
  /// Stabilization specification.
  stabilization_spec stabilization_spec_;
};
