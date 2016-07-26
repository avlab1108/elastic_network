#include "video_data_preparer_task.h"

#include <utils.h>
#include <config.h>
#include <node_chooser.h>

#include <core_application.h>

#include <iostream>
#include <fstream>
#include <string>

int video_data_preparer_task::execute()
{
  // TODO: check for emptiness
  const auto& command_line = core_application::instance()->get_command_line();
  const std::size_t arg_count = command_line.get_unrecognized_options().size();
  if(arg_count < 2)
  {
    return -1;
  }
  const std::string& input = command_line.get_unrecognized_options()[1];
  bool excitation = true;
  bool relaxation = true;
  if(arg_count > 3)
  {
    const std::string& mode = command_line.get_unrecognized_options()[3];
    excitation = mode.empty() || mode == "e" || mode =="a";
    relaxation = mode.empty() || mode == "r" || mode =="a";
  }
  std::size_t freq = 1;
  if(arg_count > 5)
  {
    const std::string& freq_str = command_line.get_unrecognized_options()[5];
    freq = std::stoul(freq_str);
  }
  const std::string& output = get_work_directory();
  const links_t& links = get_config()->get_user_settings().get_network().get_links();
  std::map<std::size_t, std::set<std::size_t>> sorted_links;
  for(auto it = links.begin(); it != links.end(); ++it)
  {
    sorted_links_[it->first].insert(it->second);
    sorted_links_[it->second].insert(it->first);
  }

  optimal_nodes_ = get_config()->get_user_settings().get_visualization_nodes();
  if(optimal_nodes_.empty())
  {
    node_chooser nodes(get_config()->get_user_settings().get_network());
    optimal_nodes_ = nodes.choose();
  }

  std::size_t time = 0;

  int result = 0;

  if(excitation)
  {
    const std::string& excitation_input{input + "/" + "excitation.txt"};
    const std::string& excitation_output_dir{output + "/excitation/data"};
    result = convert(time, freq, excitation_input, excitation_output_dir);
  }
  if(0 != result)
  {
    return result;
  }

  if(relaxation)
  {
    std::string relaxation_input{input + "/" + "relaxation.txt"};
    const std::string& relaxation_output_dir{output + "/relaxation/data"};
    result = convert(time, freq, relaxation_input, relaxation_output_dir);
  }
  return result;
}

int video_data_preparer_task::convert(std::size_t& start_time, const std::size_t freq, const std::string& input_file, const std::string& output)
{
  std::ifstream input(input_file);
  if(!input.is_open())
  {
    return -1;
  }
  utils::create_directory(output);
  std::string line;
  std::vector<std::string> read_lines;
  while(std::getline(input, line))
  {
    if(!line.empty())
    {
      read_lines.push_back(line);
    }
    else
    {
      if(0 == start_time++ % freq)
      {
        std::string a(output + "/" + std::to_string(start_time) + ".txt");
        std::ofstream out(a);
        if(!out.is_open())
        {
          continue;
        }
        std::vector<std::pair<std::string, std::string>> links;
        for(std::size_t ind = 0; ind < read_lines.size(); ++ind)
        {
          out << read_lines[ind] << '\n';
          auto links_it = sorted_links_.find(ind);
          if(sorted_links_.end() != links_it)
          {
            for(auto link_it = links_it->second.begin(); link_it != links_it->second.end(); ++link_it)
            {
              links.emplace_back(read_lines[ind], read_lines[*link_it]);
            }
          }
        }
        out << '\n' << '\n';
        for(std::size_t ind = 0; ind < links.size(); ++ind)
        {
          out << links[ind].first << '\n' << links[ind].second << '\n' << '\n' << '\n';
        }
        for(std::size_t i = 0; i < optimal_nodes_.size(); ++i)
        {
          out << read_lines[optimal_nodes_[i]] << '\n';
        }
        out.close();
      }
      read_lines.clear();
    }
  }
  return 0;
}
