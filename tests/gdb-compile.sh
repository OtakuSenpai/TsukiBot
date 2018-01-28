#!/usr/bin/env sh

g++ -c -ggdb3 ../TsukiBot/src/constants.cpp -I ../TsukiBot/include
g++ -c -ggdb3 ../TsukiBot/src/ircmessage.cpp -I ../TsukiBot/include
#g++ -ggdb3 ircmessage-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
g++ -ggdb3 msg-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
