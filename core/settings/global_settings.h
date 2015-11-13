#pragma once

#include <string>

class global_settings
{
public:
  global_settings();
  void set_results_dir(const std::string& dir);
  const std::string& get_results_dir() const;

  void set_trajectory_output_dir(const std::string& dir);
  const std::string& get_trajectory_output_directory() const;

  void set_excitation_output_file(const std::string& dir);
  const std::string& get_excitation_output_file() const;

  void set_relaxation_output_file(const std::string& dir);
  const std::string& get_relaxation_output_file() const;

private:
  std::string results_dir_;
  std::string trajectory_output_dir_;
  std::string excitation_output_dir_;
  std::string relaxation_output_dir_;
};
