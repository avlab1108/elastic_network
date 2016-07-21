#include "force_generator.h"

#include <utils.h>

force_generator::force_generator(const forces_spec& fspec) :
  fspec_(fspec)
{
  generate_forces();
}

forces_t force_generator::generate()
{
  if(fspec_.dynamic)
  {
    generate_forces();
  }
  return result_;
}

void force_generator::generate_forces()
{
  result_.clear();
  result_.resize(fspec_.nodes.size());
  double n = 0.0;
  for(std::size_t i = 0; i < fspec_.nodes.size(); ++i)
  {
    result_[i] = std::make_pair(fspec_.nodes[i], utils::random_point());
    n += norm(result_[i].second);
  }
  const double d = fspec_.fs/std::sqrt(n);
  for(std::size_t i = 0; i < fspec_.nodes.size(); ++i)
  {
    result_[i].second *= d;
  }
}

