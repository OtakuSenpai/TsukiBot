#include "mooplg.hpp"

TRYX_DECL_PLUGIN(MooPlg)
SET_PLUGIN_NAME("MooPlg")
SET_PLUGIN_TYPE("HelperPlgs")
SET_PLUGIN_VERS("2")

MooPlg :: MooPlg() {

}

MooPlg :: ~MooPlg() {

}

char* MooPlg :: onCommand(const char* name) {
  srand(time(NULL));
  int random = rand()%3;
  const char *temp1 = ": ";
  char *retValue = NULL,*temp2 = NULL;
  int length = strlen(name);
  temp2 = (char*) calloc(sizeof(name)+3,sizeof(char));
  strcat(temp2,name); strcat(temp2,temp1);
  length = 0;
  
  switch(random){
    case 0:  length = strlen(temp2) + strlen("\u000309,01m\x0f\u000302,07o\x0f\u000305,13o\x0f\u000310,06o\x0f\u000307,14!!!\x0f");
             retValue = (char*)calloc(length+1,sizeof(char));
             strcat(retValue,temp2);             
             strcat(retValue,"\u000309,01m\x0f\u000302,07o\x0f\u000305,13o\x0f\u000310,06o\x0f\u000307,14!!!\x0f");
             break;
    
    case 1:  length = strlen(temp2) + strlen("\u000310,06m\x0f\u000311,13o\x0f\u000308,04o\x0f\u000314,03o\x0f\u000307,14!!!\x0f");
             retValue = (char*)calloc(length+1,sizeof(char));
             strcat(retValue,temp2);             
             strcat(retValue,"\u000310,06m\x0f\u000311,13o\x0f\u000308,04o\x0f\u000314,03o\x0f\u000307,14!!!\x0f"); 
             break;
             
    case 2:  length = strlen(temp2) + strlen("\u000305,13m\x0f\u000309,01o\x0f\u000310,06o\x0f\u000311,13o\x0f\u000307,14!!!\x0f");
             retValue = (char*)calloc(length+1,sizeof(char));
             strcat(retValue,temp2);             
             strcat(retValue,"\u000305,13m\x0f\u000309,01o\x0f\u000310,06o\x0f\u000311,13o\x0f\u000307,14!!!\x0f");
             break;
             
    default: length = strlen(temp2) + strlen("\u000306,08m\x0f\u000302,05o\x0f\u000307,09o\x0f\u000305,13o\x0f\u000307,14!!!\x0f");
             retValue = (char*)calloc(length+1,sizeof(char));
             strcat(retValue,temp2);             
             strcat(retValue,"\u000306,08m\x0f\u000302,05o\x0f\u000307,09o\x0f\u000305,13o\x0f\u000307,14!!!\x0f");
  }
  
  return retValue;
}
