#include <iostream>
#include <string>
#include <sstream>
#include "../TsukiBot/include/ircmessage.hpp"
#include "../TsukiBot/include/constants.hpp"

using namespace Tsuki;

int main() {

  std::string s1 = ":kornbluth.freenode.net 353 G33kb0i = #tsukibot :G33kb0i dx_ob";
  std::string s2(":hobana.freenode.net 366 G33kb0i #tsukibot :End of /NAMES lst.");

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
   
   s1.clear(); m1.clear();
   s1 = ":hitchcock.freenode.net 372 G33kb0i :- Falanx Cyber Security, Private Internet Access and Yubico for footing the bill.";
   m1.handleParse(s1);
   std::cout<<"Message 1\n"
           <<"Total: "<<m1.getData()<<std::endl
           <<"Prefix: "<<m1.getPrefix()<<std::endl
           <<"Command: "<<m1.getCommand()<<std::endl
           <<"Packet: "<<static_cast<int>(m1.getPacketInfo())<<std::endl
           <<"Sender: "<<m1.getSender()<<std::endl
           <<"Content: "<<m1.getContent()<<std::endl;

  return 0;
}
