/**
 * @file eigens.h
 * @brief This file contains @ref eigens class.
 * @author Minas Hovhannisyan
 */

#include <linearization_matrix.h>

#include <armadillo>

/**
 * @class eigens
 * @brief Calculates eigenvalues and eigenvectors of given matrix.
 */
class eigens
{
public:
  /**
   * @brief Constructs eigens objecti for provided matrix.
   * @param matrix Input matrix.
   */
  eigens(const linearization_matrix& matrix);

  /**
   * @brief Returns eigenvalues.
   * @return Eigenvalues.
   */
  const arma::vec& get_values() const;
  /**
   * @brief Returns eigenvectors.
   * @return Eigenvectors.
   */
  const arma::mat& get_vectors() const;

private:
  /// Linearization matrix.
  linearization_matrix matrix_;
  /// Eigenvalues.
  arma::vec values_;
  /// Eigenvectors.
  arma::mat vectors_;
};
