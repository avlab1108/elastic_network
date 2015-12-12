#include "node_chooser.h"
#include <eigens.h>

#include <armadillo>

node_chooser::node_chooser(const network& net) :
  net_(net)
{
  eigens es(net);
  const arma::mat& vectors = es.get_vectors();
  const arma::vec& values = es.get_values();

  std::size_t index = 0;
  double min = values(index++);
  while(std::fabs(min) < 0.00001 && index < values.n_elem)
  //while(min < 0.00001)
  {
    min = values(index++);
  }
  arma::vec e1 = vectors.col(index - 1);
  arma::vec e2 = vectors.col(index);

  double e1_norm = 0.0;
  for(std::size_t i = 0; i < e1.n_elem; i += 3)
  {
    point_type e_i{e1(i), e1(i+1), e2(i+2)};
    e1_norm += abs(e_i) * abs(e_i);
  }
  if(0 != e1_norm)
  {
    e1 = e1/e1_norm;
  }

  double e2_norm = 0.0;
  for(std::size_t i = 0; i < e2.n_elem; i += 3)
  {
    point_type e_i{e2(i), e2(i+1), e2(i+2)};
    e2_norm += abs(e_i) * abs(e_i);
  }
  if(0 != e2_norm)
  {
    e2 = e2/e2_norm;
  }

  double max_change = 0.0;
  std::size_t node1 = 0, node2 = 0;
  #pragma omp parallel for
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    const point_type& p1 = net_.get_node_position(i);
    point_type e1_i{e1(3*i), e1(3*i+1), e1(3*i+2)};
    #pragma omp parallel for
    for(std::size_t j = i+1; j < net_.get_size(); ++j)
    {
      point_type e1_j{e1(3*j), e1(3*j+1), e1(3*j+2)};
      const point_type& p2 = net_.get_node_position(j);
      double rel = std::fabs(scalar_prod(e1_i - e1_j, p1 - p2)/abs(p1 - p2));
      if(rel > max_change)
      {
        node1 = i;
        node2 = j;
        max_change = rel;
      }
    }
  }
  node_numbers_.push_back(node1);
  node_numbers_.push_back(node2);
  std::cout << "1-> " << node1 << " 2-> " << node2 << " max-> " << max_change << std::endl;

  max_change = 0.0;
  std::size_t node3 = 0;
  const point_type& p1 = net_.get_node_position(node1);
  point_type e2_i{e2(3*node1), e2(3*node1+1), e2(3*node1+2)};
  #pragma omp parallel for
  for(std::size_t j = 0; j < net_.get_size(); ++j)
  {
    point_type e2_j{e2(3*j), e2(3*j+1), e2(3*j+2)};
    const point_type& p2 = net_.get_node_position(j);
    double rel = std::fabs(scalar_prod(e2_i - e2_j, p1 - p2)/abs(p1 - p2));
    if(rel > max_change)
    {
      node3 = j;
      max_change = rel;
    }
  }
  node_numbers_.push_back(node3);
  std::cout << "3-> " << node3 << " max-> " << max_change << std::endl;
}

const node_chooser::node_numbers_type& node_chooser::choose() const
{
  return node_numbers_;
}
