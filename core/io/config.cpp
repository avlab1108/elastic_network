#include "config.h"
#include <global_settings_importer.h>
#include <user_settings_importer.h>

config::config(const std::string& user_config)
{
  load_global_settings();
  load_user_settings(user_config);
}

const global_settings& config::get_global_settings() const
{
  return global_;
}

const user_settings& config::get_user_settings() const
{
  return user_;
}

void config::load_global_settings()
{
  const std::string global_settings_path = "./global_config.yaml";
  global_ = global_settings_importer(global_settings_path).get_settings();
}

void config::load_user_settings(const std::string& file_name)
{
  user_ = user_settings_importer(file_name).get_settings();
}
