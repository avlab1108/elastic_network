#include <task_manager.h>
#include <trajectory_task.h>
#include <utils.h>
#include <user_settings_importer.h>
#include <user_settings.h>

#include <cstdlib>
#include <memory>

int main()
{
  task_manager& manager = task_manager::instance();

  config c("./config.yaml");
  trajectory_process task1(12, c);
  task1.execute();
  return 0;
}
