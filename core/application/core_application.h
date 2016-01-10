#pragma once

#include <command_line.h>

#include <memory>
#include <ctime>

class user_settings;
class global_settings;
class base_task;
class config;

class core_application
{
public:
  core_application(int argc, char** argv, const std::shared_ptr<base_task>& task);

  const std::shared_ptr<config>& get_config() const;

  std::string get_work_directory() const;

  int execute();

  static core_application* instance();

protected:
  void set_timestamp(const std::time_t t);
  void prepare_work_directory();
  void assign_task(const std::shared_ptr<base_task>& task);

  virtual void pre_execute();
  virtual void post_execute();

protected:
  static core_application* instance_;

protected:
  std::time_t timestamp_;

private:
  command_line command_line_;
  std::shared_ptr<config> config_;
  std::shared_ptr<base_task> task_;
};
