#include "utils.h"

namespace utils
{

point_type random_point()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(-0.5, 0.5);
  double x = dis(gen);
  double y = dis(gen);
  double z = dis(gen);
  return point_type(x, y, z);
}

long double distance(const point_type& p1, const point_type& p2)
{
  return abs(p1-p2);
}

}
