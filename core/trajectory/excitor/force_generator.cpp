#include "force_generator.h"

#include <random>

force_generator::force_generator(const double fs, const nodes_type& nodes) :
  fs_(fs),
  nodes_(nodes)
{
  result_.reserve(nodes_.size());
}

namespace
{
point_type random_point()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  double x = dis(gen);
  double y = dis(gen);
  double z = dis(gen);
  return point_type(x, y, z);
}
}

const force_generator::result_type& force_generator::generate()
{
  //Frand=(rand(3*Nuz,1)-ones(3*Nuz,1)/2);%случайная сила
  //Frand=(Frand*Rand_norm)/norm(Frand);%нормируем случайную силу на Rand_norm

  double n = 0.0;
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result_[i] = std::make_pair(nodes_[i], random_point() - point_type(0.5, 0.5, 0.5));
    n += norm(result_[i].second);
  }
  for(std::size_t i = 0; i < nodes_.size(); ++i)
  {
    result_[i].second *= fs_/n;
  }
  return result_;
}

