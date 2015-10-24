#pragma once

#include <point.h>

class force_generator
{
public:
  typedef point<double, 3> force_type;
  typedef std::vector<force_type> result_type;

  force_generator(const double fs, const std::size_t count);

  const result_type& generate();

private:
  const double fs_;
  const std::size_t count_;
  result_type result_;
};
