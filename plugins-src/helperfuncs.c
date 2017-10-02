#include "helperfuncs.h"

List tokenizer(const char* data) {
  char* var = (char*) calloc(1,strlen(data) +1);
  List<char*> ll;
  strcpy(var,data);
  char* token = strtok(var," ");
  while(token != NULL) {
    ll.pushBack(token);
    token = strtok(NULL," ");
  }
  return ll;
} 

size_t find(const char data,const char* words) {
  size_t pos = 0;
  for(size_t i = 0; i<strlen(words); ++i) {
	if(data == words[i]) {
      pos = i; break;
    }
  }
  if(pos == 0) return -1;
  return pos;
}

size_t find(const char* findIt,const char* data) {
  char* var = (char*) calloc(1,strlen(data)+1);
  strcpy(var,data);
  char* pos = strstr(var,findIt);
  if(!pos) return -1;
  else return (size_t)(pos-var);
}
