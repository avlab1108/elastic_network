#include "task.h"

process::~process()
{
}

void task::run()
{
  for(auto it = processes_.begin(); it != processes_.end(); ++it)
  {
    (*it)->execute();
  }
}

void task::add_process(const std::shared_ptr<process>& process)
{
  processes_.push_back(process);
}
