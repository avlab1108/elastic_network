/**
 * @file network.h
 * @brief This file contains @a network class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <point.h>
#include <common_types.h>

#include <boost/dynamic_bitset.hpp>

#include <vector>

/**
 * @class network
 * @brief Class represents network structure.
 *
 * Network is represented with node positions and links between them.
 * Nodes are numbered [0, network size) and can be accessed through their index.
 * Each link is represented as a pair of numbers which are node indexes.
 */
class network
{
public:
  /**
   * @brief Default constructor.
   */
  network();
  /**
   * @brief Construct network with given @a size.
   *
   * @param size Network size.
   */
  network(const std::size_t size);
  /**
   * @brief Constructs network with provided node positions and cutoff distance.
   *
   * @param node_positions Node positions.
   * @param l0 Cutoff distance.
   */
  network(const node_positions_type& node_positions, const double l0);
  /**
   * @brief Constructs network with provided node positions and links.
   *
   * @param node_positions Node positions.
   * @param links Links.
   */
  network(const node_positions_type& node_positions, const links_type& links);

  /**
   * @brief Applies @a l0 cutoff distance to the network.
   *        This means that all the nodes, which are at the distance below @a lo
   *        are connected with link.
   * @param l0 Cutoff distance value.
   */
  void set_cutoff_distance(const double l0);

  /**
   * @brief Adds link between nodes @a node1 and @a node2.
   *
   * @param node1 First node index.
   * @param node2 Second node index.
   */
  void add_link(const std::size_t node1, const std::size_t node2);

  /**
   * @brief Returns positions of all nodes in network.
   *
   * @return Node positions.
   */
  const node_positions_type& get_node_positions() const;
  /**
   * @brief Returns positions of all nodes in network.
   *
   * @return Node positions.
   */
  node_positions_type& get_node_positions();

  /**
   * @brief Sets links in the network.
   *
   * @param links Links.
   */
  void set_links(const links_type& links);
  /**
   * @brief Returns all links in network.
   *
   * @return Links.
   */
  links_type get_links() const;

  /**
   * @brief Returns position of node with index @a node.
   *
   * @param node Node index.
   * @return Position of node.
   */
  const point_type& get_node_position(const std::size_t node) const;
  /**
   * @brief Sets position of node with index @a node to @a p.
   *
   * @param node Node index.
   * @param p Position.
   */
  void set_node_position(const std::size_t node, const point_type& p);

  /**
   * @brief Returns boolean indicating whether provided nodes are connected in network.
   *
   * @param node1 First node index.
   * @param node2 Second node index.
   * @return True id @a node1 and @a node2 are connected, false otherwise.
   */
  bool are_connected(const std::size_t node1, const std::size_t node2) const;

  /**
   * @brief Sets size of network (count of nodes in network).
   *
   * @param size Size of network.
   */
  void set_size(const std::size_t size);
  /**
   * @brief Returns size of network.
   *
   * @return Size of network.
   */
  const std::size_t get_size() const;

private:
  /**
   * @brief Converts pair of node indexes into a single index to the array of links.
   *
   * @param node1 First node index.
   * @param node2 Second node index.
   * @return Index into the array of connections.
   */
  const std::size_t node_pair_to_index(const std::size_t node1, const std::size_t node2) const;

private:
  /// Node positions.
  node_positions_type nodes_;
  /// Array of links.
  boost::dynamic_bitset<> links_;
};
