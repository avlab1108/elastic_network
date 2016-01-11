#include "optimal_nodes_task.h"

#include <standalone_application.h>

#include <memory>

int main(int argc, char** argv)
{
  standalone_application app(argc, argv, std::make_shared<optimal_nodes_task>());
  return app.execute();
}
