#pragma once

#include "global_settings.h"
#include "user_settings.h"
#include "global_settings_io.h"
#include "user_settings_io.h"

class config
{
public:
  config(const std::string& user_config, const std::string& global_settings);

  const global_settings& get_global_settings() const;
  const user_settings& get_user_settings() const;
  user_settings& get_user_settings();

  std::string get_work_directory() const;

  void set_timestamp(const std::time_t t);
  const std::time_t get_timestamp() const;

  void dump();

private:
  user_settings_io user_;
  global_settings_io global_;
  std::time_t timestamp_;
};
