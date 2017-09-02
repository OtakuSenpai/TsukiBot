#define TRYX_SOURCE 1

#include "config.hpp"
#include "helperfuncs.h"

char* tokenizer(const char* data) {
  int sizeOfStr = 0,iter1 = 0;
  int countOfWords = 0;
  while(data[iter1] != '\0') {
    if(data[iter1] == ' ')
      ++countOfWords;
      ++iter1;
  }   
  
)
  
