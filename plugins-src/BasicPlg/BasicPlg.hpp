#ifndef BASICPLG_HPP
#define BASICPLG_HPP

#include "BasePlugin.hpp"

#define TRYX_SOURCE 1

class BasicPlg : public BasePlugin {
  public:
    TRYX_API_EXP BasicPlg();
    TRYX_API_EXP ~BasicPlg();
    TRYX_API_EXP char* onCall(const char* data);
    TRYX_API_EXP char* onCommand(const char* ident, const char* d);

    const char* triggered(const char* message);
    void setSubTriggers(const char* data);
    const char* getTrigStr();
    const char* getDescription();
    bool getAdminRequired();
    const char* getSubTriggers();
};

#endif
