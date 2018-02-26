#ifndef BASEPLUGIN_HPP
#define BASEPLUGIN_HPP

#define TRYX_SOURCE 1

#include <string>
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "config.hpp"

using namespace Tryx;

class BasePlugin : public PluginInterface {
  public:
    TRYX_API_EXP BasePlugin(const char* trigger, const char* dscrpt,
                            const bool& adminReq,const char* subTrigs);
    TRYX_API_EXP virtual ~BasePlugin()=0;
    TRYX_API_EXP virtual char* onCommand(const char* ident, const char* data)=0;

    virtual char* onCall(const char* data)=0;

    const char* getTrigStr();
    const char* getDescription();
    bool getAdminRequired();
    const char* getSubTriggers();

    virtual const char* triggered(const char* message)=0;

    void setSubTriggers(const char* data);

  protected:
    std::string trigStr;
    std::string description;
    bool adminRequired;
    std::vector<std::string> subTriggers;
    std::string subTriggerStr;
};


#endif
