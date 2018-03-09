#include <iostream>
#include <string>
#include <sstream>
#include "../TsukiBot/include/ircmessage.hpp"
#include "../TsukiBot/include/constants.hpp"

using namespace Tsuki;

int main() {

  std::string s1 = ":nick!user@host QUIT :Ping timeout: 200 seconds";
  std::string s2(":wgma!~wgma00@2607:fea8:3160:420:c0a9:cccd:cc6e:c047 JOIN #freenode");

  IRCMessage m1(s1);
  IRCMessage m2(s2);

  std::cout<<"Message 1\n"
           <<"Total: "<<m1.getData()<<std::endl
           <<"Prefix: "<<m1.getPrefix()<<std::endl
           <<"Command: "<<m1.getCommand()<<std::endl
           <<"Packet: "<<static_cast<int>(m1.getPacketInfo())<<std::endl
           <<"Sender: "<<m1.getSender()<<std::endl
           <<"Content: "<<m1.getContent()<<std::endl
           <<"Message 2\n"
           <<"Total: "<<m2.getData()<<std::endl
           <<"Prefix: "<<m2.getPrefix()<<std::endl
           <<"Command: "<<m2.getCommand()<<std::endl
           <<"Packet: "<<static_cast<int>(m2.getPacketInfo())<<std::endl
           <<"Sender: "<<m2.getSender()<<std::endl
           <<"Content: "<<m2.getContent()<<std::endl;

  return 0;
}
