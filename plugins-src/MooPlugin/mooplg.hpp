#ifndef MOOPLG_HPP
#define MOOPLG_HPP

#define TRYX_SOURCE 1

#include "config.hpp"

#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace Tryx;

class MooPlg : public PluginInterface
{
  public:
    TRYX_API_EXP MooPlg();
    TRYX_API_EXP virtual ~MooPlg();
    TRYX_API_EXP char* onCommand(const char* name);
};

#endif
