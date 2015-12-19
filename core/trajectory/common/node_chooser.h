/**
 * @file node_chooser.h
 * @brief This file contains @a node_chooser class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <network.h>

/**
 * @class node_chooser
 * @brief Class calculates 3 nodes for visualization.
 *
 * They are choosen in following way:
 *
 * [Citation from "Nonlinear relaxation dynamics in elastic networks and design principles of molecular machines" Yuichi Togashi, and Alexander S. Mikhailov]
 *
 * Around the equilibrium conformation, relative changes \f$p_{ij}^{(\alpha)}\f$
 * in the distances \f$u_{ij}\f$ between nodes \f$i\f$ and \f$j\f$ in a
 * relaxation mode \f$\alpha\f$ are calculated as \f$p_{ij}^{(\alpha)} = \frac{\partial u_{ij}}{\partial X_{\alpha}} = \frac{\bf{e}_{ij}^{(\alpha)}\cdot{\bf{u}_{ij}^{(0)}}}{u_{ij}^{(0)}}\f$, where \f$\bf{e}_{ij}^{(\alpha)}=\bf{e}_i^{(\alpha)}-\bf{e}_j^{(\alpha)}, \bf{u}_{ij}^{(0)} = \bf{R}_i^{(0)}-\bf{R}_j^{(0)}\f$ and \f$u_{ij}^{(0)} = \left|\bf{u}_{ij}^{(0)}\right|\f$.
 * Here the eigenvectors are normalized as \f$\sum \limits_{i} \left|\bf{e}_i^{(\alpha)}\right|^2=1\f$.
 * For trajectory visualizations, three labels (1, 2, and 3) are
 * attached to a network and distances \f$u_{12}, u_{13}\f$ and \f$u_{23}\f$ between them
 * are recorded. The labels are chosen in such a way that \f$\left|p_{12}^{(1)}\right|\f$, the
 * relative distance change in the slowest relaxation mode, is maximal
 * between the nodes labeled as 1 and 2; then the third node is chosen
 * for which \f$\left|p_{13}^{(2)}\right|\f$, in the second slowest relaxation mode, is maximal
 * between the nodes labeled as 1 and 3.
 */
class node_chooser
{
public:
  /// Container for node indexes.
  typedef std::vector<std::size_t> node_numbers_type;

public:
  /**
   * @brief Constructs node_chooser from provided network.
   *
   * @param net Network.
   */
  node_chooser(const network& net);
  /**
   * @brief Returns choosen nodes.
   *
   * @return Node indexes.
   */
  const node_numbers_type& choose() const;

private:
  /// Network.
  const network& net_;
  /// Node indexes.
  node_numbers_type node_numbers_;
};
