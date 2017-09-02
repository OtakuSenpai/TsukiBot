#ifndef MOOPLG_HPP
#define MOOPLG_HPP

#define TRYX_SOURCE 1

#if defined _WIN32
  #define TRYX_API_EXP __declspec(dllexport)
#elif defined __GNUC__
  #define TRYX_API_EXP __attribute__((visibility("default")))
#endif

#include "config.hpp"

#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace Tryx;

class MooPlg : public PluginInterface
{
  public:
    TRYX_API_EXP MooPlg();
    TRYX_API_EXP ~MooPlg();
    TRYX_API_EXP char* onCommand(const char* name);
};

#endif
