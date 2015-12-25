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

std::string config::get_work_directory() const
{
  std::stringstream dir;
  std::tm* ptm = std::localtime(&timestamp_);
  char buf[50];
  strftime(buf, sizeof(buf), "%Y.%m.%d_%H.%M.%S", ptm);
  const global_settings& gs = global_.get_settings();
  dir << gs.get_results_dir() << "_" << buf;
  return dir.str();
}

void config::dump()
{
  user_.export_settings(get_work_directory());
  global_.export_settings(get_work_directory());
}

void config::set_timestamp(const std::time_t t)
{
  timestamp_ = t;
}

const std::time_t config::get_timestamp() const
{
  return timestamp_;
}
