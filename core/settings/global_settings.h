#pragma once

#include <string>

class global_settings
{
public:
  global_settings();

  void set_results_dir(const std::string& dir);
  const std::string& get_results_dir() const;

  void set_generation_dir(const std::string& dir);
  const std::string& get_generation_dir() const;

  void set_excitation_file_name(const std::string& file_name);
  const std::string& get_excitation_file_name() const;

  void set_relaxation_file_name(const std::string& file_name);
  const std::string& get_relaxation_file_name() const;

  void set_trajectory_file_name(const std::string& file_name);
  const std::string& get_trajectory_file_name() const;

  void set_eigens_file_name(const std::string& file_name);
  const std::string& get_eigens_file_name() const;

  void set_nodes_file_name(const std::string& file_name);
  const std::string& get_nodes_file_name() const;

  void set_dump_data(const bool dump);
  const bool get_dump_data() const;

  void set_dump_step(const std::size_t step);
  const std::size_t get_dump_step() const;

  void set_time_limit(const std::size_t limit);
  const std::size_t get_time_limit() const;

private:
  std::string results_dir_;
  std::string generation_dir_;
  std::string excitation_file_name_;
  std::string relaxation_file_name_;
  std::string trajectory_file_name_;
  std::string eigens_file_name_;
  std::string nodes_file_name_;
  bool dump_data_;
  std::size_t dump_step_;
  std::size_t time_limit_;
};
