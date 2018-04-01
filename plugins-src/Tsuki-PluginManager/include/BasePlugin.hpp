///////////////////////////////////////////////////////////////////////////////////
// TsukiBot IRC Bot made by Avra Neel Chakraborty                                //
//                                                                               //
// Copyright (c) 2018 Avra Neel Chakraborty                                      //
//                                                                               //
// This Source Code Form is subject to the terms of the Mozilla Public           //
// License, v. 2.0. If a copy of the MPL was not distributed with this           //
// file, You can obtain one at http://mozilla.org/MPL/2.0/.                      //
//                                                                               //
// The above copyright notice and this permission notice shall be included in    //
// all copies or substantial portions of the Software.                           //
///////////////////////////////////////////////////////////////////////////////////

#define TSUKI_SOURCE 1

#ifndef BASEPLUGIN_HPP
#define BASEPLUGIN_HPP

#include "config.hpp"

#if defined _WIN32
  #define TSUKI_API_EXP __declspec(dllexport)
#elif defined __GNUC__
  #define TSUKI_API_EXP __attribute__((visibility("default")))
#endif

#include <string>
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

namespace Tsuki {

  class BasePlugin {
    public:
      TSUKI_API_EXP BasePlugin(const char* trigger, const char* dscrpt,
                              const bool& adminReq,const char* subTrigs);
      TSUKI_API_EXP virtual ~BasePlugin()=0;
      TSUKI_API_EXP virtual char* onCommand(const char* ident, const char* data)=0;

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
}


#endif
