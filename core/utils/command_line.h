/**
 * @file command_line.h
 * @brief This file contains @ref command_line class.
 * @author Minas Hovhannisyan
 */

#include <string>
#include <vector>

/**
 * @class command_line
 * @brief Parses command line arguments of application startup.
 *
 * Extract following 2 arguments from command line:\n
 * 1) -u User settings file name.\n
 * 2) -g Global settings file name.
 */
class command_line
{
public:
  /**
   * @brief Constructs @ref command_line object.
   * @param argc Arguments count.
   * @param argv Argument strung values.
   */
  command_line(int argc, char** argv);
  /**
   * @brief Returns user settings file name.
   * @return User settings file name.
   */
  const std::string& get_user_settings_path() const;
  /**
   * @brief Returns global settings file name.
   * @return Global settings file name.
   */
  const std::string& get_global_settings_path() const;

  /**
   * @brief Returns unrecognized options.
   * @return Unrecognized options.
   */
  const std::vector<std::string>& get_unrecognized_options() const;

private:
  /// User settings file name.
  std::string user_settings_path_;
  /// Global settings file name.
  std::string global_settings_path_;
  /// Unrecognized options.
  std::vector<std::string> unrecognized_options_;
};
