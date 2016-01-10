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

  void dump(const std::string& output_dir);

private:
  user_settings_io user_;
  global_settings_io global_;
};
