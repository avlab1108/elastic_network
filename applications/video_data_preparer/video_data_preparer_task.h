/**
 * @file video_data_preparer_task.h
 * @brief This file contains @ref video_data_preparer_task class.
 * @author Minas Hovhannisyan
 */

#pragma once

#include <base_task.h>

#include <vector>
#include <string>
#include <map>
#include <set>

/**
 * @class video_data_preparer_task
 * @brief Creates video from input directory.
 */
class video_data_preparer_task : public base_task
{
public:
  /**
   * @brief Base interface override.
   * @return Execution status.
   */
  virtual int execute() override;
  
private:
  int convert(std::size_t& start_time, const std::size_t freq, const std::string& input_file, const std::string& output);

private:
  std::map<std::size_t, std::set<std::size_t>> sorted_links_;
  std::vector<std::size_t> optimal_nodes_;
};
