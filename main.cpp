#include <iostream>
#include <cstdlib>

#include "TsukiIRC.hpp"

using namespace Tsuki;

int main()
{
  std::string server{"irc.freenode.net"},nick{"G33kb0i"},realname{"G33kb0i"},pass;
  std::string user{"OtakuSenpai"},channel{"##chatterz"},nick2{"Falguni"};
  unsigned int port = 6667;

  Channel chan(channel);
  User usr(user);
  std::string msg;

  Bot *bot = new Bot(server,channel,nick,nick2,user,realname,pass,port);
  bot->Connect();

  bot->Disconnect();
  std::cout<<"Exiting program now."<<std::endl;
  delete bot;
  return 0;
}
