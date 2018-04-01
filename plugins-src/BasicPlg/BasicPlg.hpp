#ifndef BASICPLG_HPP
#define BASICPLG_HPP

#include "BasePlugin.hpp"

#define TSUKI_SOURCE 1

using namespace Tsuki;

class BasicPlg : public BasePlugin {
  public:
    TSUKI_API_EXP BasicPlg();
    TSUKI_API_EXP ~BasicPlg();
    TSUKI_API_EXP char* onCall(const char* data);
    TSUKI_API_EXP char* onCommand(const char* ident, const char* d);

    const char* triggered(const char* message);
    void setSubTriggers(const char* data);
    const char* getTrigStr();
    const char* getDescription();
    bool getAdminRequired();
    const char* getSubTriggers();
};

#endif
