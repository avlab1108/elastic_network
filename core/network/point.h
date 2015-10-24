#pragma once

#include <boost/operators.hpp>
#include <ostream>

template<class T, const std::size_t Dim>
class point :
  boost::additive1<point<T, Dim>,
  boost::additive2<point<T, Dim>, T,
  boost::multiplicative2<point<T, Dim>, T>>>
{
public:
  const static std::size_t dim = Dim;
  typedef T value_type;
  typedef point<value_type, dim> point_type;

  point()
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinartes_[i] = T();
    }
  }

  point(const value_type val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] = val;
    }
  }

  point(const value_type x, const value_type y, const value_type z)
  {
    if(dim > 0)
    {
      coordinates_[0] = x;
    }
    if(dim > 1)
    {
      coordinates_[1] = y;
    }
    if(dim > 2)
    {
      coordinates_[2] = z;
    }
  }

  T operator[](const std::size_t i) const
  {
    return coordinates_[i];
  }

  T& operator[](const std::size_t i)
  {
    return coordinates_[i];
  }

  point_type& operator+=(const point_type& p)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] += p[i];
    }
    return *this;
  }

  point_type& operator-=(const point_type& p)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] -= p[i];
    }
    return *this;
  }

  point_type& operator+=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] += val;
    }
    return *this;
  }

  point_type& operator-=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] -= val;
    }
    return *this;
  }

  point_type& operator*=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] *= val;
    }
    return *this;
  }

  point_type& operator/=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] /= val;
    }
    return *this;
  }

private:
  T coordinates_[dim];
};

template< class T, std::size_t Dim >
point<T, Dim> operator-(const point<T, Dim>& p)
{
  point<T, Dim> tmp;
  for(std::size_t i = 0; i < dim; ++i) tmp[i] = -p[i];
  return tmp;
}

template< class T, std::size_t Dim >
T scalar_prod(const point<T, Dim>& p1,const point<T, Dim>& p2)
{
  T tmp = 0.0;
  for(std::size_t i = 0; i < dim; ++i) tmp += p1[i] * p2[i];
  return tmp;
}

template< class T, std::size_t Dim >
T norm(const point<T, Dim>& p1)
{
  return scalar_prod(p1, p1);
}

template< class T, std::size_t Dim >
T abs(const point<T, Dim>& p1)
{
  return sqrt(norm(p1));
}

template< class T, std::size_t Dim >
std::ostream& operator<<(std::ostream &out, const point<T, Dim>& p)
{
  if(Dim > 0)
  {
    out << p[0];
  }
  for(std::size_t i = 1; i < dim; ++i)
  {
    out << " " << p[i];
  }
  return out;
}



#endif //POINT_TYPE_HPP_INCLUDED
