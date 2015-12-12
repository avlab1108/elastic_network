#include <linearization_matrix.h>

#include <armadillo>

class eigens
{
public:
  eigens(const linearization_matrix& matrix);

  const arma::vec& get_values() const;
  const arma::mat& get_vectors() const;

private:
  linearization_matrix matrix_;
  arma::vec values_;
  arma::mat vectors_;
};
