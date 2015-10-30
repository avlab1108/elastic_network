#pragma once

#include <string>

class importer
{
public:
  importer();

  void import_config(const std::string& file_name);
};
