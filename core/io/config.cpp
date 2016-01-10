#include "config.h"
#include <global_settings_io.h>
#include <user_settings_io.h>

#include <chrono>

#include <boost/filesystem.hpp>

config::config(const std::string& user_config, const std::string& global_config)
{
  user_.import_settings(user_config);
  global_.import_settings(global_config);
}

const global_settings& config::get_global_settings() const
{
  return global_.get_settings();
}

const user_settings& config::get_user_settings() const
{
  return user_.get_settings();
}

user_settings& config::get_user_settings()
{
  return user_.get_settings();
}

void config::dump(const std::string& output_dir)
{
  user_.export_settings(output_dir);
  global_.export_settings(output_dir);
}
