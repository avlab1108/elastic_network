#include "force_generator.cpp"

#include <random>

force_generator::force_generator(const double fs, const std::size_t count) :
  fs_(fs),
  count_(count)
{
  result_.reserve(count);
}

namespace
{
point random_point()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);
  double x = dis(gen);
  double y = dis(gen);
  double z = dis(gen);
  return point(x, y, z);
}
}

const result_type& force_generator::generate()
{
  //Frand=(rand(3*Nuz,1)-ones(3*Nuz,1)/2);%случайная сила
  //Frand=(Frand*Rand_norm)/norm(Frand);%нормируем случайную силу на Rand_norm

  double n = 0.0;
  for(std::size_t i = 0; i < count_; ++i)
  {
    result_[i] = random_point() - point(0.5, 0.5, 0.5);
    n += norm(result_[i]);
  }
  for(std::size_t i = 0; i < count_; ++i)
  {
    result_[i] *= fs_/n;
  }
  return result_;
}

