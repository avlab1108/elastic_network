#pragma once

#include <fstream>

class logger
{
public:
  enum severity
  {
    info,
    warning,
    error,
    critical
  };

public:
  static logger& instance();

public:
  void append(severity s, const std::string& message);

private:
  logger(const std::string& file_name);
  logger(const logger& l) = delete;
  ~logger();
  logger& operator=(const logger& l) = delete;

private:
  std::ofstream log_;
};

#define LOG(s_, m_) \
{ \
  logger& l = logger::instance(); \
  l.append( (s_), (m_) ); \
}
