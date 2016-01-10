#pragma once

#include "core_application.h"

#include <memory>

class base_task;

class standalone_application : public core_application
{
public:
  standalone_application(int argc, char** argv, const std::shared_ptr<base_task>& task);
};
