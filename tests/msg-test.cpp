#include <iostream>
#include <string>
#include "../TsukiBot/include/ircmessage.hpp"

using namespace Tsuki;

int main() {

  std::string s1(":weber.freenode.net NOTICE * :*** Looking up your hostname...");
  std::string s2(":weber.freenode.net 001 G33kb0i :Welcome to the freenode Internet Relay Chat Network G33kb0i");
  IRCMessage m1(s1),m2(s2);

  std::cout<<"Message 1\n"
           <<"Prefix: "<<m1.getPrefix()<<std::endl
           <<"Command: "<<m1.getCommand()<<std::endl
           <<"Packet: "<<static_cast<int>(m1.getPacketInfo())<<std::endl
           <<"Sender: "<<m1.getSender()<<std::endl
           <<"Content: "<<m1.getContent()<<std::endl
           <<"Message 2\n"
           <<"Prefix: "<<m2.getPrefix()<<std::endl
           <<"Command: "<<m2.getCommand()<<std::endl
           <<"Packet: "<<static_cast<int>(m2.getPacketInfo())<<std::endl
           <<"Sender: "<<m2.getSender()<<std::endl
           <<"Content: "<<m2.getContent()<<std::endl;
  return 0;
}
