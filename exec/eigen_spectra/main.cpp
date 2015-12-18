#include <command_line.h>
#include <eigens.h>
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
  eigens e(n);
  utils::create_directory(c.get_work_directory());
  const std::string& eigen_file_name = c.get_work_directory() + "/" + c.get_global_settings().get_eigens_file_name();
  std::ofstream out(eigen_file_name);
  if(!out.is_open())
  {
    std::cerr << "Cannot create output file." << std::endl;
    return 1;
  }
  out << "#Eigenvalues" << std::endl;
  out << e.get_values() << std::endl;
  out << "#Eigenvectors" << std::endl;
  out << e.get_vectors() << std::endl;
  out.close();
  return 0;
}
