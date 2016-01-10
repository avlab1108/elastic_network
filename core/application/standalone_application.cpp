#include "standalone_application.h"

#include <chrono>

standalone_application::standalone_application(int argc, char** argv, const std::shared_ptr<base_task>& task) :
  core_application(argc, argv, task)
{
  using std::chrono::system_clock;
  timestamp_ = system_clock::to_time_t(system_clock::now());
  instance_ = this;
}
