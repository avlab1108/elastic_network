#include "base_task.h"

#include <config.h>
#include <core_application.h>

base_task::~base_task()
{
}

const std::shared_ptr<config>& base_task::get_config() const
{
  return core_application::instance()->get_config();
}

std::string base_task::get_work_directory() const
{
  return core_application::instance()->get_work_directory();
}

proxy_task::proxy_task()
{
}

proxy_task::proxy_task(const std::shared_ptr<base_task>& real_task) :
  real_task_(real_task)
{
}

void proxy_task::pre_execute()
{
}

int proxy_task::execute()
{
  int status = 0;
  pre_execute();
  if(real_task_)
  {
    status = real_task_->execute();
  }
  post_execute();
  return status;
}

void proxy_task::post_execute()
{
}

void proxy_task::assign_task(const std::shared_ptr<base_task>& task)
{
  real_task_ = task;
}

int complex_task::execute()
{
  int status = 0;
  for(auto it = tasks_.begin(); it != tasks_.end(); ++it)
  {
    //TODO maybe something better
    status += (*it)->execute();
  }
  return status;
}

void complex_task::add_task(const std::shared_ptr<base_task>& task)
{
  tasks_.push_back(task);
}
