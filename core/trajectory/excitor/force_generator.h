#pragma once

#include <point.h>

#include <vector>

class force_generator
{
public:
  typedef point_type force_type;
  typedef std::vector<std::size_t> nodes_type;
  typedef std::vector<std::pair<std::size_t, force_type>> result_type;

  force_generator(const double fs, const nodes_type& nodes);

  result_type generate();

private:
  const double fs_;
  const nodes_type nodes_;
};
