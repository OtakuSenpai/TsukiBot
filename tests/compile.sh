#!/usr/bin/env sh

g++ -c ../TsukiBot/src/constants.cpp -I ../TsukiBot/include
g++ -c ../TsukiBot/src/ircmessage.cpp -I ../TsukiBot/include
g++ -o msg-test msg-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
g++ -o ircmsg-file-test ircmessage-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
g++ -o prefix-test prefix-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
g++ -o parse-test parsemsg-test.cpp ircmessage.o constants.o -I ../TsukiBot/include
