/**
 * @file linearization_matrix.h
 * @brief This file contains @ref linearization_matrix class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <network.h>

#include <armadillo>

/**
 * @class linearization_matrix
 * @brief Calculates linearization matrix for provided network.
 *
 * Matrix is calculated with following formulas:
 *
 * \f[
 * \Lambda_{ij} |_{i\not{=}j} = - A_{ij} \frac{1}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} \begin{pmatrix}
 * \left(X_i^0-X_j^0\right)^2                       & \left(X_i^0-X_j^0\right)\left(Y_i^0-Y_j^0\right) & \left(X_i^0-X_j^0\right)\left(Z_i^0-Z_j^0\right) \\
 * \left(X_i^0-X_j^0\right)\left(Y_i^0-Y_j^0\right) & \left(Y_i^0-Y_j^0\right)^2                       & \left(Y_i^0-Y_j^0\right)\left(Z_i^0-Z_j^0\right) \\
 * \left(X_i^0-X_j^0\right)\left(Z_i^0-Z_j^0\right) & \left(Y_i^0-Y_j^0\right)\left(Z_i^0-Z_j^0\right) & \left(Z_i^0-Z_j^0\right)^2
 * \end{pmatrix}
 * \f]
 *
 * \f[
 * \Lambda_{ij} |_{i=j} = \begin{pmatrix}
 * \sum \limits_{j=1}^N A_{ij} \frac{\left(X_i^0-X_j^0\right)^2}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2}                       & \sum \limits_{j=1}^N A_{ij} \frac{\left(X_i^0-X_j^0\right)\left(Y_i^0-Y_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} & \sum \limits_{j=1}^N A_{ij} \frac{\left(X_i^0-X_j^0\right)\left(Z_i^0-Z_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} \\
 * \sum \limits_{j=1}^N A_{ij} \frac{\left(X_i^0-X_j^0\right)\left(Y_i^0-Y_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} & \sum \limits_{j=1}^N A_{ij} \frac{\left(Y_i^0-Y_j^0\right)^2}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2}                       & \sum \limits_{j=1}^N A_{ij} \frac{\left(Y_i^0-Y_j^0\right)\left(Z_i^0-Z_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} \\
 * \sum \limits_{j=1}^N A_{ij} \frac{\left(X_i^0-X_j^0\right)\left(Z_i^0-Z_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} & \sum \limits_{j=1}^N A_{ij} \frac{\left(Y_i^0-Y_j^0\right)\left(Z_i^0-Z_j^0\right)}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2} & \sum \limits_{j=1}^N A_{ij} \frac{\left(Z_i^0-Z_j^0\right)^2}{\left|\vec{R}_i^{(0)} - \vec{R}_j^{(0)}\right|^2}
 * \end{pmatrix}
 * \f]
 *
 * where \f$\vec{R}_i^{(0)} = (X_i^0, Y_i^0, Z_i^0)\f$ and \f$A_{ij}\f$ are elements of adjacency matrix of input network.
 *
 */
class linearization_matrix
{
public:
  /**
   * @brief Constructs linearization_matrix object for provided network.
   * @param net Network.
   */
  linearization_matrix(const network& net);
  /**
   * @brief Returns constructed matrix.
   * @return Linearization matrix.
   */
  const arma::mat& get_matrix() const;
  /**
   * @brief Returns size of linearization matrix.
   * @return Linearization matrix size.
   */
  const std::size_t get_size() const;

private:
  /// Network.
  network net_;
  /// Linearization matrix.
  arma::mat m_;
};
