#include "core_application.h"

#include <base_task.h>
#include <config.h>
#include <logging.h>
#include <utils.h>

#include <chrono>

core_application* core_application::instance_ = nullptr;

core_application::core_application(int argc, char** argv, const std::shared_ptr<base_task>& task) :
  command_line_(argc, argv),
  config_(std::make_shared<config>(command_line_.get_user_settings_path(), command_line_.get_global_settings_path())),
  task_(task)
{
  assert(task_);
}

const std::shared_ptr<config>& core_application::get_config() const
{
  return config_;
}

std::string core_application::get_work_directory() const
{
  std::stringstream dir;
  std::tm* ptm = std::localtime(&timestamp_);
  char buf[50];
  strftime(buf, sizeof(buf), "%Y.%m.%d_%H.%M.%S", ptm);
  const global_settings& gs = config_->get_global_settings();
  dir << gs.get_results_dir() << "_" << buf;
  return dir.str();
}

int core_application::execute()
{
  if(task_)
  {
    pre_execute();
    int status = task_->execute();
    post_execute();
    return status;
  }
  return 0;
}

core_application* core_application::instance()
{
  if(nullptr == instance_)
  {
    std::string message = "Instance of application should be created before trying to access it.";
    LOG(logger::critical, message);
    assert(!message.c_str());
  }
  return instance_;
}

void core_application::prepare_work_directory()
{
  utils::create_directory(get_work_directory());
}

void core_application::pre_execute()
{
  prepare_work_directory();
}

void core_application::post_execute()
{
  config_->dump(get_work_directory());
}
