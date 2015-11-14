#pragma once

#include "global_settings.h"
#include "user_settings.h"

class config
{
public:
  config(const std::string& user_config, const std::string& global_settings);
  const global_settings& get_global_settings() const;
  const user_settings& get_user_settings() const;

private:
  void load_user_settings(const std::string& file_name);
  void load_global_settings(const std::string& file_name);

private:
  user_settings user_;
  global_settings global_;
};
