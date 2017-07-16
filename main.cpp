#include <iostream>
#include <chrono>

#include "TsukiIRC.hpp"

using namespace Tsuki;

int main()
{
  std::string server{"irc.freenode.net"},nick{"G33kb0i"},realname{"G33kb0i"},pass=" ";
  std::string user{"Bhsdns"},channel{"#cplusplus.com"};
  unsigned int port = 6667;

  Channel chan(channel);
  User usr(user);
  std::string msg;

  Bot *bot = new Bot(server,channel,nick,user,pass,port);
  bot->Connect();

  bot->Disconnect();
  std::cout<<"Exiting program now."<<std::endl;
  delete bot;
  return 0;
}
