#include "force_generator.h"

#include <utils.h>

force_generator::force_generator(const double fs, const nodes_type& nodes) :
  fs_(fs),
  nodes_(nodes)
{
}

force_generator::result_type force_generator::generate()
{
  //Frand=(rand(3*Nuz,1)-ones(3*Nuz,1)/2);%случайная сила
  //Frand=(Frand*Rand_norm)/norm(Frand);%нормируем случайную силу на Rand_norm

  result_type result;
  result.resize(nodes_.size());
  long double n = 0.0;
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i] = std::make_pair(nodes_[i], utils::random_point());
    n += std::pow(abs(result[i].second), 2);
  }
  const long double d = fs_/std::sqrt(n);
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i].second *= d;
  }
  return result;
}

