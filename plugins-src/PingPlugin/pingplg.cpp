#include "pingplg.hpp"

TRYX_DECL_PLUGIN(PingPlg)
SET_PLUGIN_NAME("PingPlg")
SET_PLUGIN_TYPE("HelperPlgs")
SET_PLUGIN_VERS("1")

PingPlg :: PingPlg() {
	
}

PingPlg :: ~PingPlg() {
	
}

char* PingPlg :: onCommand(const char* name) {
  const char* tempVar = "\001ACTION pings ";
  char* retValue = (char*) calloc(1,strlen(name) + strlen(tempVar) + 9);
  strcpy(retValue,tempVar); strcat(retValue,name);
  strcat(retValue,"\001\r\n");
  return retValue;
}		
