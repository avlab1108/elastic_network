#pragma once

#include <cstdlib>

class settings
{
public:
  settings();

  void setFs(const double fs);
  const double fs() const;

  void setTimeLimit(const std::size_t limit);
  const std::size_t timeLimit() const;

private:
  double fs_;
  std::size_t timeLimit_;
};
