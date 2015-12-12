#include "linearization_matrix.h"

#include <omp.h>

linearization_matrix::linearization_matrix(const network& net) :
  net_(net),
  m_(3*net.get_size(), 3*net.get_size(), arma::fill::zeros)
{
  // creating linearization matrix
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      if(i != j)
      {
        if(i == j || !net_.are_connected(i, j))
        {
          continue;
        }
        // block not on diagonal
        const point_type& p1 = net_.get_node_position(i);
        const point_type& p2 = net_.get_node_position(j);

        double x_i_j = p1[0] - p2[0];
        double y_i_j = p1[1] - p2[1];
        double z_i_j = p1[2] - p2[2];

        m_(3*i,   3*j)   = x_i_j * x_i_j;
        m_(3*i,   3*j+1) = x_i_j * y_i_j;
        m_(3*i,   3*j+2) = x_i_j * z_i_j;

        m_(3*i+1, 3*j)   = y_i_j * x_i_j;
        m_(3*i+1, 3*j+1) = y_i_j * y_i_j;
        m_(3*i+1, 3*j+2) = y_i_j * z_i_j;

        m_(3*i+2, 3*j)   = z_i_j * x_i_j;
        m_(3*i+2, 3*j+1) = z_i_j * y_i_j;
        m_(3*i+2, 3*j+2) = z_i_j * z_i_j;
      }
      else
      {
        // block on diagonal 
        const point_type& p1 = net_.get_node_position(i);
        for(std::size_t k = 0; k < net_.get_size(); ++k)
        {
          if(i == k || !net_.are_connected(i, k))
          {
            continue;
          }
          const point_type& p2 = net_.get_node_position(k);

          double x_i_k = p1[0] - p2[0];
          double y_i_k = p1[1] - p2[1];
          double z_i_k = p1[2] - p2[2];

          m_(3*i,   3*k)   += x_i_k * x_i_k;
          m_(3*i,   3*k+1) += x_i_k * y_i_k;
          m_(3*i,   3*k+2) += x_i_k * z_i_k;

          m_(3*i+1, 3*k)   += y_i_k * x_i_k;
          m_(3*i+1, 3*k+1) += y_i_k * y_i_k;
          m_(3*i+1, 3*k+2) += y_i_k * z_i_k;

          m_(3*i+2, 3*k)   += z_i_k * x_i_k;
          m_(3*i+2, 3*k+1) += z_i_k * y_i_k;
          m_(3*i+2, 3*k+2) += z_i_k * z_i_k;
        }
      }
    }
  }
}

const arma::mat& linearization_matrix::get_matrix() const
{
  return m_;
}

const std::size_t linearization_matrix::get_size() const
{
  return 3*net_.get_size();
}
