#include "BasicPlg.hpp"

#include <time.h>
#include <sstream>

TRYX_DECL_PLUGIN(BasicPlg)
SET_PLUGIN_NAME("BasicPlg")
SET_PLUGIN_TYPE("helperss")
SET_PLUGIN_VERS("0.1")

BasicPlg :: BasicPlg(): BasePlugin("basic","This plugin contains basic commands to help in daily channel maintanence like help and list, and also contains commands to play with like ping,coffee,tea and moo",
                        false,"help moo ping coffeee tea list") {

}

BasicPlg :: ~BasicPlg() {

}

//$base moo
//$base ping letty
//$base coffee letty

char* BasicPlg :: onCall(const char* data) {
  char* retValue;
  std::string msg(data),subtrigger,otherContent,ret;
  bool hasit = false;

  msg = msg.substr(1);

  if(trigStr == msg.substr(0,msg.find(' '))) {
    msg = msg.substr(msg.find(' ')+1);
    subtrigger = msg.substr(0,msg.find(' '));
    otherContent = msg.substr(msg.find(' ')+1);

    for(auto&& i: subTriggers) {
      if(i == subtrigger) { hasit = true; break;}
      else { continue; }
    }

    if(!hasit) {
      ret = "Incorrect command, no such option!!!";
    }
    else if(hasit) {
      srand(time(NULL));

      if(subtrigger == "moo") {
        std::string temp = otherContent;
        temp = otherContent.substr(0,otherContent.find(' '));
        int random = rand()%3;
        switch(random) {
          case 0:  temp = temp + ": " +
          "\u000309,01m\x0f\u000302,07o\x0f\u000305,13o\x0f\u000310,06o\x0f\u000307,14!!!\x0f";
                   ret = temp;
                   break;
          case 1:  temp = temp + ": " +
          "\u000310,06m\x0f\u000311,13o\x0f\u000308,04o\x0f\u000314,03o\x0f\u000307,14!!!\x0f";
                   ret = temp;
                   break;
          case 2:  temp = temp + ": " +
          "\u000305,13m\x0f\u000309,01o\x0f\u000310,06o\x0f\u000311,13o\x0f\u000307,14!!!\x0f";
                   ret = temp;
                   break;
          default: temp = temp + ": " +
          "\u000306,08m\x0f\u000302,05o\x0f\u000307,09o\x0f\u000305,13o\x0f\u000307,14!!!\x0f";
                   ret = temp;
                   break;
        }
      }
      else if(subtrigger == "ping") {
        if(otherContent.empty()) {
          ret = "\001ACTION pong ";
        }
        else {
          std::string name = otherContent.substr(0,otherContent.find(' '));
          ret = "\001ACTION pings " + name;
        }
        ret = ret + "\001\r\n";
      }
    }
  }

  retValue = (char*) calloc(ret.size(), sizeof(char));
  strcpy(retValue,ret.c_str());
  return retValue;
}

char* BasicPlg :: onCommand(const char* ident, const char* d) {
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

const char* BasicPlg :: triggered(const char* message) {
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

void BasicPlg :: setSubTriggers(const char* data) {
  std::string msg(data);
  std::stringstream s(msg);
  for(std::string temp; std::getline(s,temp,' '); ) {
    subTriggers.push_back(temp);
  }
}

const char* BasicPlg :: getTrigStr() { return trigStr.c_str(); }
const char* BasicPlg :: getDescription() { return description.c_str(); }
bool BasicPlg :: getAdminRequired() { return adminRequired; }

const char* BasicPlg :: getSubTriggers() {
  return subTriggerStr.c_str();
}
