#include "eigens.h"

eigens::eigens(const linearization_matrix& matrix) :
  matrix_(matrix),
  values_(matrix.get_size(), arma::fill::zeros),
  vectors_(matrix.get_size(), matrix.get_size(), arma::fill::zeros)
{
  arma::eig_sym(values_, vectors_, matrix_.get_matrix());
}

const arma::vec& eigens::get_values() const
{
  return values_;
}

const arma::mat& eigens::get_vectors() const
{
  return vectors_;
}
