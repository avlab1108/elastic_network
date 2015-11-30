#include "eigens.h"

#include <omp.h>

eigens::eigens(const network& net) :
  net_(net),
  values_(3*net.get_size(), arma::fill::zeros),
  vectors_(3*net.get_size(), 3*net.get_size(), arma::fill::zeros)
{
  arma::mat m(3*net_.get_size(), 3*net_.get_size(), arma::fill::zeros);
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

        m(3*i,   3*j)   = a_i_j * x_i_j * x_i_j;
        m(3*i,   3*j+1) = a_i_j * x_i_j * y_i_j;
        m(3*i,   3*j+2) = a_i_j * x_i_j * z_i_j;

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
        for(std::size_t k = 0; k < net_.get_size(); ++k)
        {
          const point_type& p2 = net_.get_node_position(k);

          double x_i_k = p1[0] - p2[0];
          double y_i_k = p1[1] - p2[1];
          double z_i_k = p1[2] - p2[2];

          unsigned a_i_k = net_.are_connected(i, k) ? 1 : 0;

          m(3*i,   3*k)   += a_i_k * x_i_k * x_i_k;
          m(3*i,   3*k+1) += a_i_k * x_i_k * y_i_k;
          m(3*i,   3*k+2) += a_i_k * x_i_k * z_i_k;

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

  arma::eig_sym(values_, vectors_, m);
}

const arma::vec& eigens::get_values() const
{
  return values_;
}

const arma::mat& eigens::get_vectors() const
{
  return vectors_;
}
