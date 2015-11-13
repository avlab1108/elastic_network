#pragma once

#include "global_settings.h"
#include "user_settings.h"

class config
{
public:
  config(const std::string& user_config);
  const global_settings& get_global_settings() const;
  const user_settings& get_user_settings() const;

private:
  void load_global_settings();
  void load_user_settings(const std::string& file_name);

private:
  global_settings global_;
  user_settings user_;
};
