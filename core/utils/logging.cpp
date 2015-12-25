#include "logging.h"

#include <iostream>
#include <map>
#include <cassert>

#include <boost/interprocess/sync/file_lock.hpp>

namespace
{
std::map<logger::severity, std::string> severity_helper =
{
  {logger::info, "Info"},
  {logger::warning, "Warning"},
  {logger::error, "Error"},
  {logger::critical, "Critical"}
};

}

logger::logger(const std::string& file_name) :
  log_(file_name, std::ios_base::app)
{
  if(!log_.good())
  {
    std::cerr << "[Warning]: Cannot open log file. Logging will be unavailable." << std::endl;
  }
}

logger::~logger()
{
  log_.close();
}

logger& logger::instance()
{
  static logger l("./log.txt");
  return l;
}

void logger::append(severity s, const std::string& message)
{
  if(log_.good())
  {
    auto it = severity_helper.find(s);
    assert(severity_helper.end() != it);
    boost::interprocess::file_lock flock("./log.txt");
    log_ << "[" << it->second << "]: " << message << std::endl;
  }
}

