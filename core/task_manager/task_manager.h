#pragma once

class task_manager
{
public:
  static task_manager& instance();

  void distribute_tasks();

private:
  task_manager();
};
