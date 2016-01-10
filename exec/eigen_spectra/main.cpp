#include "eigen_spectra_task.h"

#include <standalone_application.h>

#include <memory>

int main(int argc, char** argv)
{
  standalone_application app(argc, argv, std::make_shared<eigen_spectra_task>());
  return app.execute();
}
