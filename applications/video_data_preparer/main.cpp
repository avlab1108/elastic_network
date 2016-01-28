#include "video_data_preparer_task.h"

#include <standalone_application.h>

#include <memory>

int main(int argc, char** argv)
{
  standalone_application app(argc, argv, std::make_shared<video_data_preparer_task>());
  return app.execute();
}
