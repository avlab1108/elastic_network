#include <string>

class command_line
{
public:
  command_line(int argc, char** argv);
  const std::string& get_user_settings_path() const;
  const std::string& get_global_settings_path() const;

private:
  std::string user_settings_path_;
  std::string global_settings_path_;
};
