/**
 * @file config.h
 * @brief This file contains @ref config class.
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
   * @brief Dumps config into working directory.
   * @param output_dir Directory to dump configuration into.
   *
   * Configuration is stored in "config" directory in provided directory.
   * All settings, which were used during work process (including generated ones) are dumped.
   */
  void dump(const std::string& output_dir);

private:
  /// User settings i/o controller.
  user_settings_io user_;
  /// Global settings i/o controller.
  global_settings_io global_;
};
