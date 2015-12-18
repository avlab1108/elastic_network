#include <command_line.h>
#include <node_chooser.h>
#include <config.h>

#include <iostream>
#include <fstream>
#include <chrono>

int main(int argc, char** argv)
{
  command_line cm(argc, argv);
  config c(cm.get_user_settings_path(), cm.get_global_settings_path());
  using std::chrono::system_clock;
  c.set_timestamp(system_clock::to_time_t(system_clock::now()));
  const network& n = c.get_user_settings().get_network();
  node_chooser nc(n);
  utils::create_directory(c.get_work_directory());
  const std::string& nodes_file_name = c.get_work_directory() + "/" + c.get_global_settings().get_nodes_file_name();
  std::ofstream out(nodes_file_name);
  if(!out.is_open())
  {
    std::cerr << "Cannot create output file." << std::endl;
    return 1;
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
