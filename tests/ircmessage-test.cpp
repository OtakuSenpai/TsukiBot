#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "ircmessage.hpp"

using namespace Tsuki;

int main() {
  IRCMessage msg;
  std::string temp;
  std::ifstream fio;
  fio.open("irclog.txt", std::ios::in);
  if(fio.bad() || fio.fail()) {
    std::cout<<"Bad file operation!";
    exit(0);
  }
  while(std::getline(fio,temp,'\n')) {
    msg.handleParse(temp);
    std::cout<<"Total: "<<msg.getData()<<std::endl
                
             <<"Prefix: "<<msg.getPrefix()<<std::endl
             <<"Command: "<<msg.getCommand()<<std::endl
             <<"Packet: "<<static_cast<int>(msg.getPacketInfo())<<std::endl
             <<"Sender: "<<msg.getSender()<<std::endl
             <<"Content: "<<msg.getContent()<<std::endl<<std::endl;
    msg.clear();
  }
  fio.close();
  return 0;
}
