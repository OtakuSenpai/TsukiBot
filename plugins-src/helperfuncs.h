#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <string.h>
#include <ctype.h>

#include "list.hpp"

List tokenizer(const char* data);
size_t find(const char data,const char* words);
size_t find(const char* data,const char* words);

#endif
