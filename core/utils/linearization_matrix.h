/**
 * @file linearization_matrix.h
 * @brief This file contains @a linearization_matrix class.
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
 * //TODO add formulas for linearization matrix calculation
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
