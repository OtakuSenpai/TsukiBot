#ifndef BASEPLUGIN_HPP
#define BASEPLUGIN_HPP

#include <string>

#include "config.hpp"

namespace Tsuki {
  class BasePlugin {
	public:
	  TRYX_API_EXP BasePlugin(const std::string& ts, const std::string& dscrpt,
	                          const bool& adminReq = false) {}
	  TRYX_API_EXP virtual BasePlugin() {} 
	  TRYX_API_EXP virtual std::string onCommand(const std::string& packet
	  
	  virtual bool triggered(const IRCMessage& msg) {
		return p.type == 
	                                        
	protected: 
	  std::string trigStr;
	  std::string description;
	  bool adminRequired;
  };
}
