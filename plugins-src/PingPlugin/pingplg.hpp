#ifndef PINGPLG_HPP
#define PINGPLG_HPP

#define TRYX_SOURCE 1

#include  "config.hpp"

#include <string.h>
#include <stdlib.h>

using namespace Tryx;

class PingPlg : public PluginInterface
{
  public:
    TRYX_API_EXP PingPlg();
    TRYX_API_EXP virtual ~PingPlg();
    TRYX_API_EXP char* onCommand(const char* name);
};

#endif
