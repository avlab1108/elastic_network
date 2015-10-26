#include "force_generator.h"

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
  double n = 0.0;
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i] = std::make_pair(nodes_[i], random_point() - point_type(0.5, 0.5, 0.5));
    n += norm(result[i].second);
  }
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result[i].second *= fs_/n;
  }
  return result;
}

