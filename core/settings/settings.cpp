#include "settings.h"

settings::settings()
{
}

void settings::setFs(const double fs)
{
  fs_ = fs;
}

const double settings::fs() const
{
  return fs_;
}

void settings::setTimeLimit(const std::size_t limit)
{
  timeLimit_ = limit;
}

const std::size_t settings::timeLimit() const
{
  return timeLimit_;
}
