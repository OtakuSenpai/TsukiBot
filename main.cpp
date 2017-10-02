#include <iostream>
#include <cstdlib>

#include "TsukiIRC.hpp"

using namespace Tsuki;

int main()
{
  try {
    std::string server{"irc.freenode.net"},nick{"G33kb0i"},realname{"G33kb0i"},pass=" ";
    std::string user{"Bhsdns"},channel{"##lazy-valoran"};
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
  catch(const std::exception& e) {
	std::cout<<"Caught exception: \n"<<e.what();
	std::exit(EXIT_FAILURE);
  }
}
