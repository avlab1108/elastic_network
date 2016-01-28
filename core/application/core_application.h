/**
 * @file core_application.h
 * @brief This file contains @ref core_application class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <command_line.h>

#include <memory>
#include <ctime>

class user_settings;
class global_settings;
class base_task;
class config;

/**
 * @class core_application
 * @brief Interface for all applications.
 *
 * Provides command line parsing, configuration i/o, work directory support and global access point.
 * Allows custom pre/post execution hooks to be defined by derived applications.
 */
class core_application
{
public:
  /**
   * @brief Constructs application with provided command line arguments and task for execution.
   * @param argc Argument count.
   * @param argv Argument values.
   * @param task Task for execution.
   */
  core_application(int argc, char** argv, const std::shared_ptr<base_task>& task);

  /**
   * @brief Access point to application config.
   * @return Application config.
   */
  const std::shared_ptr<config>& get_config() const;

  /** 
   * @brief Returns application work directory name.
   * @return Work directory name.
   *
   * Work directory name has following structure - prefix_date_time,
   * where prefix is retrieved from global config and date_time is generated at runtime.
   */
  std::string get_work_directory() const;

  /**
   * @brief Executes application and it's task.
   * @return Exit code.
   */
  int execute();

  /**
   * @brief Returns parsed command line.
   * @return Parsed command line.
   */
  const command_line& get_command_line() const;

  /**
   * @brief Global access point to application.
   * @return Application instance.
   *
   * This will return pointer to the create derived application instance.
   */
  static core_application* instance();

protected:
  /**
   * @brief Prepares work directory, e.g. checks for existence and creates if it doesn't exist.
   */
  void prepare_work_directory();

  /**
   * @brief Hook for pre-execution of task.
   */
  virtual void pre_execute();
  /**
   * @brief Hook for post-execution of task.
   */
  virtual void post_execute();

protected:
  /// Application instance.
  static core_application* instance_;

protected:
  /// Timestamp for application output directory.
  std::time_t timestamp_;

private:
  /// Command line parser.
  command_line command_line_;
  /// Configuration of application.
  std::shared_ptr<config> config_;
  /// Task for execution.
  std::shared_ptr<base_task> task_;
};
