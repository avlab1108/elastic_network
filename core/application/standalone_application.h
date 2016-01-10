/**
 * @file standalone_application.h
 * @brief This file contains @a standalone_application class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "core_application.h"

#include <memory>

class base_task;

/**
 * @class standalone_application
 * @brief Base class for standalone application.
 *
 * Provides no additional interface for derived classes.
 * Main purpose - generate timestamp for output directory name.
 */
class standalone_application : public core_application
{
public:
  /**
   * @brief Constructs application with provided command line arguments and task for execution.
   * @param argc Argument count.
   * @param argv Argument values.
   * @param task Task for execution.
   */
  standalone_application(int argc, char** argv, const std::shared_ptr<base_task>& task);
};
