#include "logging.h"

#include <iostream>
#include <map>
#include <cassert>

namespace
{
std::map<logger::severity, std::string> severity_helper =
{
  {logger::info, "Info"},
  {logger::warning, "Warning"},
  {logger::error, "Error"},
  {logger::warning, "Critical"}
};
}

logger::logger(const std::string& file_name) :
  log_(file_name)
{
  std::cerr << "[Warning]: Cannot open log file. Logging will be unavailable." << std::endl;
}

logger& logger::instance()
{
  //static logger l(global_config::instance()->log_path());
  static logger l("./log.txt");
  return l;
}

void logger::append(severity s, const std::string& message)
{
  if(log_.good())
  {
    auto it = severity_helper.find(s);
    assert(severity_helper.end() != it);
    log_ << "[" << it->second << "]: " << message << std::endl;
  }
}

