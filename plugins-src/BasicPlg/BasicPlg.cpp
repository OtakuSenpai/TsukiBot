#include "BasicPlg.hpp"

#include <time.h>
#include <sstream>
#include <iostream>

using namespace Tsuki;

TSUKI_DECL_PLUGIN(BasicPlg)
SET_PLUGIN_NAME("BasicPlg")
SET_PLUGIN_TYPE("helpers")
SET_PLUGIN_VERS("0.1")

BasicPlg :: BasicPlg(): BasePlugin("basic","This plugin contains basic commands to help in daily channel maintanence like help and list, and also contains commands to play with like ping,coffee,tea and moo",
                        false,"moo ping coffee tea dice coin cookie help") {

}

BasicPlg :: ~BasicPlg() {

}

//$basic moo
//$basic moo OtakuSenpai 
//$basic ping letty
//$basic coffee letty

char* BasicPlg :: onCall(const char* data) {
  char* retValue;
  std::string msg(data),subtrigger,otherContent,ret;
  bool hasit = false;
  std::string temp = msg.substr(0,msg.find(' '));

  if(trigStr == temp) {
    msg = msg.substr(msg.find(' ')+1);
    subtrigger = msg.substr(0,msg.find(' '));
    std::cout<<"Subtrig: "<<subtrigger<<std::endl;
    otherContent = msg.substr(msg.find(' ')+1);
    std::cout<<"Others: "<<otherContent<<std::endl;
    if(otherContent == "moo" || otherContent == "ping" ||
       otherContent == "coffee" || otherContent == "tea" ||
       otherContent == "dice" || otherContent == "coin") {
	  otherContent.clear();
    }   
      
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
		if(otherContent.empty()) {
		  ret = "\u000308,02m\x0f\u000304,06o\x0f\u000307,11o\x0f\u000310,06o\x0f\u000304,13!!!\x0f"; 
		}	
		else {   	 
          int random = rand()%3;
          switch(random) {
            case 0:  otherContent = otherContent + ": " +
                "\u000309,01m\x0f\u000302,07o\x0f\u000305,13o\x0f\u000310,06o\x0f\u000307,14!!!\x0f";
                     ret = otherContent;
                     break;
            case 1:  otherContent = otherContent + ": " +
                "\u000310,06m\x0f\u000311,13o\x0f\u000308,04o\x0f\u000314,03o\x0f\u000307,14!!!\x0f";
                     ret = otherContent;
                     break;
            case 2:  otherContent = otherContent + ": " +
                "\u000305,13m\x0f\u000309,01o\x0f\u000310,06o\x0f\u000311,13o\x0f\u000307,14!!!\x0f";
                     ret = otherContent;
                     break;
            default: otherContent = otherContent + ": " +
                "\u000306,08m\x0f\u000302,05o\x0f\u000307,09o\x0f\u000305,13o\x0f\u000307,14!!!\x0f";
                     ret = otherContent;
                     break;        
		  }
        }
      }
      else if(subtrigger == "ping") {
        if(otherContent.empty()) {
          ret = "\001ACTION pong ";
        }
        else {
          ret = "\001ACTION pings " + otherContent;
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
