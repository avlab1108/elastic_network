#include "optimal_nodes_task.h"

#include <node_chooser.h>
#include <config.h>
#include <logging.h>
#include <utils.h>

#include <fstream>

int optimal_nodes_task::execute()
{
  const std::shared_ptr<config>& c = get_config();
  const network& n = c->get_user_settings().get_network();
  node_chooser nc(n);
  utils::create_directory(get_work_directory());
  const std::string& nodes_file_name = get_work_directory() + "/" + c->get_global_settings().get_nodes_file_name();
  std::ofstream out(nodes_file_name);
  if(!out.is_open())
  {
    LOG(logger::critical, "Cannot create output file.");
    return -1;
  }
  out << "#Optimal nodes" << std::endl;
  const node_chooser::node_numbers_type& nodes = nc.choose();
  for(std::size_t i = 0; i < nodes.size(); ++i)
  {
    out << nodes[i] << std::endl;
  }
  out.close();
  return 0;
}
