#pragma once

#include <network.h>

#include <armadillo>

class linearization_matrix
{
public:
  linearization_matrix(const network& net);
  const arma::mat& get_matrix() const;
  const std::size_t get_size() const;

private:
  network net_;
  arma::mat m_;
};
