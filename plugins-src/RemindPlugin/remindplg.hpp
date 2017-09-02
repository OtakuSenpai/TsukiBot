#ifndef REMINDERPLG_HPP
#define REMINDERPLG_HPP

#define TRYX_SOURCE 1

#if defined _WIN32
  #define TRYX_API_EXP __declspec(dllexport)
#elif defined __GNUC__
  #define TRYX_API_EXP __attribute__((visibility("default")))
#endif

#include "config.hpp"

class ReminderPlg 
{
  public:
    TRYX_API_EXP ReminderPlg();
    TRYX_API_EXP ~ReminderPlg();
    TRYX_API_EXP char* onCommand(const char* data,const char* filename);
};

#endif
