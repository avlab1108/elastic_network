/**
 * @file config.h
 * @brief This file contains @a config class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include "global_settings.h"
#include "user_settings.h"
#include "global_settings_io.h"
#include "user_settings_io.h"

/**
 * @class config
 * @brief Stores and provides access to all settings.
 *
 * Holds controllers for loading and modifying user and global settings.
 */
class config
{
public:
  /**
   * @brief Constructs config from user and global settings' paths.
   */
  config(const std::string& user_config, const std::string& global_settings);

  /**
   * @brief Returns global settings.
   * @return Global settings.
   */
  const global_settings& get_global_settings() const;
  /**
   * @brief Returns user settings.
   * @return User settings.
   */
  const user_settings& get_user_settings() const;
  /**
   * @brief Returns user settings with change permissions.
   * @return User settings.
   */
  user_settings& get_user_settings();

  /**
   * @brief Returns working directory name.
   * @return Directory name.
   *
   * Directory name consists from prefix stored in global settings and timestamp, f.e. results_2015.11.26_15.55.20.
   */
  std::string get_work_directory() const;

  /**
   * @brief Sets timestamp.
   * @param t Timestamp.
   */
  void set_timestamp(const std::time_t t);
  /**
   * @brief Returns timestamp.
   * @return Timestamp.
   */
  const std::time_t get_timestamp() const;

  /**
   * @brief Dumps config into working directory.
   *
   * Configuration is stored in "config" directory in working directory.
   * All settings, which were used during work process (including generated ones) are dumped.
   */
  void dump();

private:
  /// User settings i/o controller.
  user_settings_io user_;
  /// Global settings i/o controller.
  global_settings_io global_;
  /// Timestamp for output folder naming.
  std::time_t timestamp_;
};
