#include <network.h>

#include <armadillo>

class eigens
{
public:
  eigens(const network& net);
  const arma::vec& get_values() const;
  const arma::mat& get_vectors() const;

private:
  network net_;
  arma::vec values_;
  arma::mat vectors_;
};
