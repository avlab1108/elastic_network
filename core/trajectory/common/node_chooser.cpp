#include "node_chooser.h"

#include <armadillo>

namespace
{

double projection(const point_type& r1, const point_type& r2, const point_type& r1_0, const point_type& r2_0)
{
  double d = utils::distance(r1, r2);
  double d0 = utils::distance(r1_0, r2_0);
  return (d - d0) / d0;
}

}

node_chooser::node_chooser(const network& net) :
  net_(net)
{
  arma::mat m(3*net_.get_size(), 3*net_.get_size());
  #pragma omp parallel for collapse (2)
  // creating linearization matrix
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      if(i != j)
      {
        // block not on diagonal
        const point_type& p1 = net_.get_node_position(i);
        const point_type& p2 = net_.get_node_position(j);

        double x_i_j = p1[0] - p2[0];
        double y_i_j = p1[1] - p2[1];
        double z_i_j = p1[2] - p2[2];

        unsigned a_i_j = net_.are_connected(i, j) ? 1 : 0;

        m(3*i,   3*j)     = a_i_j * x_i_j * x_i_j;
        m(3*i,   3*j+1)   = a_i_j * x_i_j * y_i_j;
        m(3*i,   3*j+2)   = a_i_j * x_i_j * z_i_j;

        m(3*i+1, 3*j)   = a_i_j * y_i_j * x_i_j;
        m(3*i+1, 3*j+1) = a_i_j * y_i_j * y_i_j;
        m(3*i+1, 3*j+2) = a_i_j * y_i_j * z_i_j;

        m(3*i+2, 3*j)   = a_i_j * z_i_j * x_i_j;
        m(3*i+2, 3*j+1) = a_i_j * z_i_j * y_i_j;
        m(3*i+2, 3*j+2) = a_i_j * z_i_j * z_i_j;
      }
      else
      {
        // block on diagonal 
        const point_type& p1 = net_.get_node_position(i);
        m(i, j) = 0;
        for(std::size_t k = 0; k < net_.get_size(); ++k)
        {
          const point_type& p2 = net_.get_node_position(k);

          double x_i_k = p1[0] - p2[0];
          double y_i_k = p1[1] - p2[1];
          double z_i_k = p1[2] - p2[2];

          unsigned a_i_k = net_.are_connected(i, k) ? 1 : 0;

          m(3*i,   3*k)     += a_i_k * x_i_k * x_i_k;
          m(3*i,   3*k+1)   += a_i_k * x_i_k * y_i_k;
          m(3*i,   3*k+2)   += a_i_k * x_i_k * z_i_k;

          m(3*i+1, 3*k)   += a_i_k * y_i_k * x_i_k;
          m(3*i+1, 3*k+1) += a_i_k * y_i_k * y_i_k;
          m(3*i+1, 3*k+2) += a_i_k * y_i_k * z_i_k;

          m(3*i+2, 3*k)   += a_i_k * z_i_k * x_i_k;
          m(3*i+2, 3*k+1) += a_i_k * z_i_k * y_i_k;
          m(3*i+2, 3*k+2) += a_i_k * z_i_k * z_i_k;
        }
      }
    }
  }

  arma::mat vectors;
  arma::vec values;
  arma::eig_sym(values, vectors, m);

  std::size_t index = 0;
  double min = values(index++);
  while(0 == min)
  {
    min = values(index++);
  }
  arma::vec e1 = vectors.col(index - 1);
  arma::vec e2 = vectors.col(index);

  std::vector<std::vector<long double>> initial_distances;
  initial_distances.resize(net_.get_size());
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    initial_distances[i].resize(net_.get_size());
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      initial_distances[i][j] = utils::distance(net_.get_node_position(i), net_.get_node_position(j));
    }
  }

  double max_change = 0.0;
  std::size_t node1 = 0, node2 = 0;
  #pragma omp parallel for
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    const point_type& p1 = net_.get_node_position(i);
    point_type e1_i{e1(i), e1(i+1), e1(i+2)};
    #pragma omp parallel for
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      if(j == i)
      {
        continue;
      }
      point_type e1_j{e1(j), e1(j+1), e1(j+2)};
      const point_type& p2 = net_.get_node_position(j);
      double rel = std::abs(scalar_prod(e1_i - e1_j, p1 - p2)/abs(p1 - p2));
      if(rel > max_change)
      {
        node1 = i;
        node2 = j;
        max_change = rel;
      }
    }
  }
  std::cout << node1 << " " << node2 << std::endl;
}

const node_chooser::node_numbers_type& node_chooser::choose() const
{
  return node_numbers_;
}
