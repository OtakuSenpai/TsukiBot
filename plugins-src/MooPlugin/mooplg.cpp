#include "mooplg.hpp"

TRYX_DECL_PLUGIN(MooPlg)
SET_PLUGIN_NAME("MooPlg")
SET_PLUGIN_TYPE("HelperPlgs")
SET_PLUGIN_VERS("0.1")

MooPlg :: MooPlg() {

}

MooPlg :: ~MooPlg() {

}

char* MooPlg :: onCommand(const char* name) {
  srand(time(NULL));
  int random = rand()%3;
  const char *temp1 = ": ";
  char *retValue = NULL;
  strcat(retValue,name); strcat(retValue,temp1);
  
  switch(random){
    case 0:  strcat(retValue,"\0039,1m\017\0032,7o\017\0035,13o\017\00310,6o\017\0037,14!!!\017");
             break;
    case 1:  strcat(retValue,"\00310,6m\017\00311,13o\017\0038,4o\017\00314,3o\017\0037,14!!!\017"); 
             break;
    case 2:  strcat(retValue,"\0035,13m\017\0039,1o\017\00310,6o\017\00311,13o\017\0037,14!!!\017");
             break;
    default: strcat(retValue,"\0036,8m\017\0032,5o\017\0037,9o\017\0035,13o\017\0037,14!!!\017");
  }
  return retValue;
}
