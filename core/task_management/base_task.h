/**
 * @file base_task.h
 * @brief This file contains @a base_task, @a proxy_task and @a complex_task classes.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <list>
#include <memory>

class config;

/**
 * @class base_task
 * @brief Interface for all tasks.
 *
 * Defines single @ref execute function for execution of task.
 */
class base_task
{
public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~base_task();
  /**
   * @brief Execute interface.
   * @return Execution status.
   */
  virtual int execute() = 0; 

  /**
   * @brief Returns global config.
   * @return Config.
   *
   * @note This method is not part of interface, it is provided only for convenience.
   */
  const std::shared_ptr<config>& get_config() const;
  /**
   * @brief Returns work directory name.
   * @return Work directory name.
   *
   * @note This method is not part of interface, it is provided only for convenience.
   */
  std::string get_work_directory() const;
};

/**
 * @class proxy_task
 * @brief Defines abstraction level upon @ref base_task for additional functionality.
 *
 * Wraps other task(s) to provide hooks for pre/post execution of real tasks.
 * Allows dynamic assignment of real task to provide higher flexibility.
 */
class proxy_task : public base_task
{
public:
  /**
   * @brief Default constructor.
   */
  proxy_task();
  /**
   * @brief Constructs wrapper task on provided task.
   * @param real_task Real task.
   */
  proxy_task(const std::shared_ptr<base_task>& real_task);

  /**
   * @brief Pre-execution hook.
   */
  virtual void pre_execute();
  /**
   * @brief Execute interface override.
   * @return Execution status.
   */
  virtual int execute() override final;
  /**
   * @brief Post-execution hook.
   */
  virtual void post_execute();

protected:
  /**
   * @brief Provides derived classes with possibility to substitute real task with new one.
   * @param task New task.
   */
  void assign_task(const std::shared_ptr<base_task>& task);

private:
  /// Real task.
  std::shared_ptr<base_task> real_task_;
};

/**
 * @class complex_task
 * @brief Allows group of similar tasks to be treated in the same way as single task.
 */
class complex_task : public base_task
{
public:
  /**
   * @brief Execute interface override.
   */
  virtual int execute() override;
  /**
   * @brief Adds new task to the list of tasks.
   * @param task New task.
   */
  void add_task(const std::shared_ptr<base_task>& task);

private:
  /// List of tasks.
  std::list<std::shared_ptr<base_task>> tasks_;
};
