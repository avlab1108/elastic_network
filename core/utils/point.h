/**
 * @file point.h
 * @brief This file contains @a point class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <boost/operators.hpp>

#include <cmath>
#include <ostream>

/**
 * @class point
 * @brief Represents point(vector) in N-ary space.
 * @tparam T Data type.
 * @tparam Dim Dimension number.
 */
template<class T, const std::size_t Dim>
class point :
  boost::additive1<point<T, Dim>,
  boost::additive2<point<T, Dim>, T,
  boost::multiplicative2<point<T, Dim>, T>>>
{
public:
  /// Dimension of point.
  const static std::size_t dim = Dim;
  /// Value type.
  typedef T value_type;
  /// Point type.
  typedef point<value_type, dim> point_type;

  /**
   * @brief Constructs point with defaults.
   */
  point()
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] = T();
    }
  }
  /**
   * @brief Contructs point using provided value for all coordinates.
   */
  point(const value_type val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] = val;
    }
  }
  /**
   * @brief Constructs 3D point.
   * @param x x coordinate.
   * @param y y coordinate.
   * @param z z coordinate.
   */
  point(const value_type x, const value_type y, const value_type z)
  {
    if(dim> 0)
    {
      coordinates_[0] = x;
    }
    if(dim> 1)
    {
      coordinates_[1] = y;
    }
    if(dim> 2)
    {
      coordinates_[2] = z;
    }
  }

  /**
   * @brief Returns value of coordinate with specified index.
   * @param i Index of coordinate.
   * @return Value of coordinate.
   */
  T operator[](const std::size_t i) const
  {
    return coordinates_[i];
  }

  /**
   * @brief Returns value of coordinate with specified index with write permissions.
   * @param i Index of coordinate.
   * @return Value of coordinate.
   */
  T& operator[](const std::size_t i)
  {
    return coordinates_[i];
  }

  /**
   * @brief In-place calculates element-wise sum with provided point.
   * @param p Right operand.
   * @return Current point with requested changes.
   */
  point_type& operator+=(const point_type& p)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] += p[i];
    }
    return *this;
  }

  /**
   * @brief In-place calculates element-wise difference with provided point.
   * @param p Right operand.
   * @return Current point with requested changes.
   */
  point_type& operator-=(const point_type& p)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] -= p[i];
    }
    return *this;
  }

  /**
   * @brief In-place calculates element-wise sum with provided value.
   * @param val Value.
   * @return Current point with requested changes.
   */
  point_type& operator+=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] += val;
    }
    return *this;
  }

  /**
   * @brief In-place calculates element-wise difference with provided value.
   * @param val Value.
   * @return Current point with requested changes.
   */
  point_type& operator-=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] -= val;
    }
    return *this;
  }

  /**
   * @brief In-place calculates element-wise product with provided value.
   * @param val Value.
   * @return Current point with requested changes.
   */
  point_type& operator*=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] *= val;
    }
    return *this;
  }

  /**
   * @brief In-place calculates element-wise quotient with provided value.
   * @param val Value.
   * @return Current point with requested changes.
   */
  point_type& operator/=(const value_type& val)
  {
    for(std::size_t i = 0; i < dim; ++i)
    {
      coordinates_[i] /= val;
    }
    return *this;
  }

private:
  /// Coordinate values.
  T coordinates_[dim];
};

/**
 * @brief Calculates reverse of point.
 * @param p Point.
 * @return Reversed point.
 */
template<class T, std::size_t Dim>
point<T, Dim> operator-(const point<T, Dim>& p)
{
  point<T, Dim> tmp;
  for(std::size_t i = 0; i < Dim; ++i)
  {
    tmp[i] = -p[i];
  }
  return tmp;
}

/**
 * @brief Calculates scalar product of 2 points(vectors).
 * @param p1 First point.
 * @param p2 Second point.
 * @return Scalar product.
 */
template<class T, std::size_t Dim>
T scalar_prod(const point<T, Dim>& p1, const point<T, Dim>& p2)
{
  T tmp = 0.0;
  for(std::size_t i = 0; i < Dim; ++i)
  {
    tmp += p1[i] * p2[i];
  }
  return tmp;
}

/**
 * @brief Calculates norm of point(vector).
 * @param p Point.
 * @return Norm.
 */
template<class T, std::size_t Dim>
T norm(const point<T, Dim>& p)
{
  return scalar_prod(p, p);
}

/**
 * @brief Calculates module of point(vector).
 * @param p Point.
 * @return Norm.
 */
template<class T, std::size_t Dim>
T abs(const point<T, Dim>& p)
{
  return std::sqrt(norm(p));
}

/**
 * @brief Prints point into provided stream.
 * @param out Stream.
 * @param p Point.
 * @return Updated stream.
 */
template<class T, std::size_t Dim>
std::ostream& operator<<(std::ostream& out, const point<T, Dim>& p)
{
  if(Dim > 0)
  {
    out << p[0];
  }
  for(std::size_t i = 1; i < Dim; ++i)
  {
    out << " " << p[i];
  }
  return out;
}
