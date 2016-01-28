#include "command_line.h"

#include <boost/program_options.hpp>

#include <iostream>

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
    po::command_line_parser parser{argc, argv};
    parser.options(desc).allow_unregistered();
    po::parsed_options parsed = parser.run();
    po::store(parsed, vm);
    po::notify(vm);
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
    unrecognized_options_ = po::collect_unrecognized(parsed.options, po::include_positional);
  }
  catch(po::error& e)
  {
    std::cerr << "\nError parsing command line: " << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
  }
}

const std::string& command_line::get_user_settings_path() const
{
  return user_settings_path_;
}

const std::string& command_line::get_global_settings_path() const
{
  return global_settings_path_;
}

const std::vector<std::string>& command_line::get_unrecognized_options() const
{
  return unrecognized_options_;
}
