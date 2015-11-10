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
