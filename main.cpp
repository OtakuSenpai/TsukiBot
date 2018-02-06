#include <iostream>
#include <cstdlib>

#include "TsukiIRC.hpp"

using namespace Tsuki;

int main() {
  std::string server{"irc.freenode.net"},nick{"G33kb0i"},realname{"G33kb0i"},pass;
  std::string user{"OtakuSenpai"},channel{"#tsukibot"},nick2{"Falguni"},special("$");
  std::string path = "./plugins/";
  unsigned int port = 6667;

  Channel chan(channel);
  User usr(user);
  std::string msg;

  Bot *bot = new Bot(server,channel,nick,nick2,user,realname,pass,port,special,path);
  bot->Connect();

  bot->Disconnect();
  std::cout<<"Exiting program now."<<std::endl;
  delete bot;
  return 0;
}
