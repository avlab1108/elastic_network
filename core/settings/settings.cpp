#include "settings.h"

settings& settings::instance()
{
  static settings global_settings;
  return global_settings;
}
