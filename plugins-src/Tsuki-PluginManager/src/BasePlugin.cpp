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

#include "BasePlugin.hpp"

#include <sstream>

using namespace Tsuki;

BasePlugin :: BasePlugin(const char* trigger, const char* dscrpt,
                         const bool& adminReq, const char* subTrigs):
                         trigStr(trigger), description(dscrpt),
                         adminRequired(adminReq),subTriggerStr(subTrigs) {
                           setSubTriggers(subTrigs);
                         }

BasePlugin :: ~BasePlugin() {

}

char* BasePlugin :: onCommand(const char* ident, const char* d) {
  std::string command(ident);
  std::string data(d);
  std::string ret;
  char* retValue;

  if(command == "onCall") {
    ret = onCall(d);
  }
  else if(command == "triggered") {
    ret = triggered(d);
  }
  else if(command == "getTrigStr") {
    ret = getTrigStr();
  }
  else if(command == "getDescription") {
    ret = getDescription();
  }
  else if(command == "getAdminRequired") {
    ret = getAdminRequired();
  }
  else if(command == "getSubTriggers") {
    ret = getSubTriggers();
  }

  retValue = (char*) calloc(ret.size(), sizeof(char));
  strcpy(retValue,ret.c_str());
  return retValue;
}

const char* BasePlugin :: triggered(const char* message) {
  std::string msg(message);
  bool found = (msg.substr(0,trigStr.size()) == trigStr);
  msg = msg.substr(trigStr.size() + 1);
  bool hasit = [](std::vector<std::string> a, std::string b) {
                   bool c;
                   for(auto&& i: a) {
                     if(b == i) { c = true; break; }
                   }
                   return c;
                 }(subTriggers,msg.substr(0,msg.find(' ')));
  return (found & hasit) ? "true" : "false";
}

void BasePlugin :: setSubTriggers(const char* data){
  std::string msg(data);
  std::stringstream s(msg);
  for(std::string temp; std::getline(s,temp,' '); ) {
    subTriggers.push_back(temp);
  }
}

const char* BasePlugin :: getTrigStr() { return trigStr.c_str(); }
const char* BasePlugin :: getDescription() { return description.c_str(); }
bool BasePlugin :: getAdminRequired() { return adminRequired; }

const char* BasePlugin :: getSubTriggers() {
  return subTriggerStr.c_str();
}
