#include "eigen_spectra_task.h"

#include <eigens.h>
#include <config.h>
#include <logging.h>
#include <utils.h>

#include <fstream>

int eigen_spectra_task::execute()
{
  eigens e(get_config()->get_user_settings().get_network());
  const std::string& eigen_file_name = get_work_directory() + "/" + get_config()->get_global_settings().get_eigens_file_name();
  std::ofstream out(eigen_file_name);
  if(!out.is_open())
  {
    LOG(logger::critical, "Cannot create output file.");
    return -1;
  }
  out << "#Eigenvalues" << std::endl;
  out << e.get_values() << std::endl;
  out.close();
  return 0;
}
