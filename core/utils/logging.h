/**
 * @file logging.h
 * @brief This file contains @ref logger class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <fstream>

/**
 * @class logger
 * @brief Provides global logging functionality.
 */
class logger
{
public:
  /**
   * @enum severity
   * @brief Decribes severity levels of logger.
   */
  enum severity
  {
    info, /**<Information*/
    warning, /**<Warning*/
    error, /**<Error*/
    critical /**<Critical error*/
  };

public:
  /**
   * @brief Global access point for instance of logger.
   * @return Logger instance.
   */
  static logger& instance();

public:
  /**
   * @brief Appends provided message with defined severity to logger stream.
   * @param s Severity of message.
   * @param message Message string.
   */
  void append(severity s, const std::string& message);

private:
  /**
   * @brief Constructs logger's instance with output being redirected to provided file.
   * @param file_name Log file.
   */
  logger(const std::string& file_name);
  /// Deleted copy constructor.
  logger(const logger& l) = delete;
  /**
   * @brief Destructs logger's instance.
   */
  ~logger();
  /// Deleted assignment operator.
  logger& operator=(const logger& l) = delete;

private:
  /// Output stream.
  std::ofstream log_;
};

/// Helper macro for emitting log messages.
#define LOG(s_, m_) \
{ \
  logger& l = logger::instance(); \
  l.append( (s_), (m_) ); \
}
