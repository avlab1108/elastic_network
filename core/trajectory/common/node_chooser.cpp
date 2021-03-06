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
  #pragma omp parallel for ordered
  for(std::size_t i = 0; i < net_.get_size(); ++i)
  {
    const point_type& p1 = net_.get_node_position(i);
    point_type e1_i{e1(3*i), e1(3*i+1), e1(3*i+2)};
    for(std::size_t j = 0; j < net_.get_size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      point_type e1_j{e1(3*j), e1(3*j+1), e1(3*j+2)};
      const point_type& p2 = net_.get_node_position(j);
      double rel = std::fabs(scalar_prod(e1_i - e1_j, p1 - p2)/abs(p1 - p2));
      #pragma omp ordered
      {
        if(rel > max_change)
        {
          node1 = i;
          node2 = j;
          max_change = rel;
        }
      }
    }
  }

  double max_change1 = 0.0;
  std::size_t node3 = 0;
  const point_type& p1 = net_.get_node_position(node1);
  point_type e2_1{e2(3*node1), e2(3*node1+1), e2(3*node1+2)};
  #pragma omp parallel for ordered
  for(std::size_t j = 0; j < net_.get_size(); ++j)
  {
    if(node1 == j || node2 == j)
    {
      continue;
    }
    point_type e2_j{e2(3*j), e2(3*j+1), e2(3*j+2)};
    const point_type& pj = net_.get_node_position(j);
    double rel = std::fabs(scalar_prod(e2_1 - e2_j, p1 - pj)/abs(p1 - pj));
    #pragma omp ordered
    {
      if(rel > max_change1)
      {
        node3 = j;
        max_change1 = rel;
      }
    }
  }

  double max_change2 = 0.0;
  std::size_t node4 = 0;
  const point_type& p2 = net_.get_node_position(node2);
  point_type e2_2{e2(3*node2), e2(3*node2+1), e2(3*node2+2)};
  #pragma omp parallel for ordered
  for(std::size_t j = 0; j < net_.get_size(); ++j)
  {
    if(node2 == j || node1 ==j)
    {
      continue;
    }
    point_type e2_j{e2(3*j), e2(3*j+1), e2(3*j+2)};
    const point_type& pj = net_.get_node_position(j);
    double rel = std::fabs(scalar_prod(e2_2 - e2_j, p2 - pj)/abs(p2 - pj));
    #pragma omp ordered
    {
      if(rel > max_change2)
      {
        node4 = j;
        max_change2 = rel;
      }
    }
  }

  if(max_change1 > max_change2)
  {
    node_numbers_.push_back(node1);
    node_numbers_.push_back(node2);
    node_numbers_.push_back(node3);
  }
  else
  {
    node_numbers_.push_back(node2);
    node_numbers_.push_back(node1);
    node_numbers_.push_back(node4);
  }

  std::cout << "1-> " << node_numbers_[0] << " 2-> " << node_numbers_[1] << " 3-> " << node_numbers_[2] << std::endl;
  std::cout << "1-> " << max_change << " 2-> " << max_change1 << " 3-> " << max_change2 << std::endl;
}

const node_chooser::node_numbers_type& node_chooser::choose() const
{
  return node_numbers_;
}
