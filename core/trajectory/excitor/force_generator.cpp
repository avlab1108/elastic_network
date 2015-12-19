#include "force_generator.h"

#include <utils.h>

force_generator::force_generator(const double fs, const nodes_type& nodes) :
  fs_(fs),
  nodes_(nodes)
{
}

force_generator::result_type force_generator::generate()
{
  result_type result;
  result.resize(nodes_.size());
  double n = 0.0;
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i] = std::make_pair(nodes_[i], utils::random_point());
    n += norm(result[i].second);
  }
  const double d = fs_/std::sqrt(n);
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i].second *= d;
  }

  return result;
}

