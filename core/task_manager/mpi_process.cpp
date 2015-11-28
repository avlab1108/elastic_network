#include "mpi_process.h"
#include "trajectory_task.h"

#include <logging.h>
#include <thread_pool.h>

#include <boost/program_options.hpp>
#include <boost/mpi/nonblocking.hpp>
#include <boost/filesystem.hpp>

#include <chrono>
#include <ctime>

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
  thread_pool::instantiate();
}

mpi_process::~mpi_process()
{
  thread_pool::destroy();
}

main_mpi_process::main_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int main_mpi_process::execute()
{
  world_.barrier();
  create_results_dir();
  const std::size_t sim_num = config_.get_user_settings().get_simulations_count();
  const int mpi_size = world_.size() - 1;
  int single_task_size = sim_num/(0 == mpi_size ? 1 : mpi_size);
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
    requests.push_back(world_.isend(i, 0, results_dir_));
    requests.push_back(world_.isend(i, 1, sim_nums));
  }
  boost::mpi::wait_all(requests.begin(), requests.end());
  if(0 != remainder)
  {
    std::vector<std::size_t> sim_nums;
    for(int j = 0; j < remainder; ++j)
    {
      sim_nums.push_back(current++);
    }
    trajectory_task t(results_dir_, sim_nums, config_);
    t.run();
  }
  return 0;
}

void main_mpi_process::create_results_dir()
{
  using std::chrono::system_clock;
  std::stringstream output_folder;
  std::time_t tt = system_clock::to_time_t(system_clock::now());
  struct std::tm* ptm = std::localtime(&tt);
  char buf[50];
  strftime(buf, sizeof(buf), "%Y.%m.%d_%H.%M.%S", ptm);
  const global_settings& gs = config_.get_global_settings();
  output_folder << gs.get_results_dir() << "_" << buf;
  boost::filesystem::path dir(output_folder.str());
  if(boost::filesystem::is_directory(dir))
  {
    LOG(logger::info, std::string("Results directory \"") + output_folder.str() + "\" already exists. Trying to use it.");
  }
  else if(!boost::filesystem::create_directory(dir))
  {
    LOG(logger::error, std::string("Failed to create output directory\"") + output_folder.str() + "\".");
  }
  results_dir_ = output_folder.str();
}

worker_mpi_process::worker_mpi_process(int argc, char** argv) :
  mpi_process(argc, argv)
{
}

int worker_mpi_process::execute()
{
  world_.barrier();
  std::string results_dir;
  world_.recv(0, 0, results_dir);
  std::vector<std::size_t> sim_nums;
  world_.recv(0, 1, sim_nums);
  trajectory_task t(results_dir, sim_nums, config_);
  t.run();
  return 0;
}
