#include "mpi_process.h"
#include "trajectory_task.h"

#include <boost/program_options.hpp>
#include <boost/mpi/nonblocking.hpp>

command_line::command_line(int argc, char** argv) :
  global_settings_path_("global_config.yaml")
{
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help,h", "Print help message")
    ("user_settings,u", po::value<std::string>()->required(), "File with user settings.")
    ("global_settings,g", po::value<std::string>(), "File with global settings.");

  po::variables_map vm;
  try
  {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if(vm.count("help"))
    {
      std::cout << "Elastic Network Modeller v1.0" << std::endl << desc << std::endl;
      return;
    }
    if(vm.count("user_settings"))
    {
      std::cout << "user settings file name = " << vm["user_settings"].as<std::string>() << std::endl;
      user_settings_path_ = vm["user_settings"].as<std::string>();
    }
    if(vm.count("global_settings"))
    {
      std::cout << "global settings file name = " << vm["global_settings"].as<std::string>() << std::endl;
      global_settings_path_ = vm["global_settings"].as<std::string>();
    }
    po::notify(vm);
  }
  catch(po::error& e)
  {
    std::cerr << "\nError parsing command line: " << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
  }
}

std::string command_line::get_user_settings_path() const
{
  return user_settings_path_;
}

std::string command_line::get_global_settings_path() const
{
  return global_settings_path_;
}

mpi_process::mpi_process(int argc, char** argv) :
  command_line_(argc, argv),
  config_(command_line_.get_user_settings_path(), command_line_.get_global_settings_path())
{
}

main_mpi_process::main_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int main_mpi_process::execute()
{
  world_.barrier();
  const std::size_t sim_num = config_.get_user_settings().get_simulations_count();
  const int mpi_size = world_.size() - 1;
  int single_task_size = sim_num/mpi_size;
  int remainder = sim_num - single_task_size * mpi_size;
  int current = 0;
  std::vector<boost::mpi::request> requests;
  for(int i = 1; i < mpi_size + 1; ++i)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < single_task_size; ++j)
    {
      sim_nums.push_back(current++);
    }
    requests.push_back(world_.isend(i, 0, sim_nums));
  }
  boost::mpi::wait_all(requests.begin(), requests.end());
  if(0 != remainder)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < remainder; ++j)
    {
      sim_nums.push_back(current++);
    }
    trajectory_task t(config_, sim_nums);
    t.run();
  }
  //world_.barrier();
  return 0;
}

worker_mpi_process::worker_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int worker_mpi_process::execute()
{
  world_.barrier();
  std::vector<std::size_t> sim_nums;
  world_.recv(0, 0, sim_nums);
  trajectory_task t(config_, sim_nums);
  t.run();
  //world_.barrier();
  return 0;
}
