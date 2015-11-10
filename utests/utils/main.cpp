#include <importer.h>
#include <utils.h>

#include <from_article.h>
#include <hierarchical_potential.h>

int main()
{
  network net1(hp::node_positions, 3);
  utils::dump_adjacency_list(net1, "./hierarchical_potential.txt");

  network net2(fa::node_positions, fa::links);

  return 0;
}
