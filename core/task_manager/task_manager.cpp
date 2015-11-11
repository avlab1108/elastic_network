#include "task_manager.h"

task_manager& task_manager::instance()
{
  static task_manager m;
  return m;
}

task_manager::task_manager()
{
}

void task_manager::distribute_tasks()
{
}
