#include<iostream>
#include <chrono>

#include "TsukiIRC.hpp"

using namespace Tsuki;
using namespace std;

int main()
{
	std::string server{"irc.freenode.net"},nick{"Bhsdns"},realname{"Bhsdns"},pass=" ";
	std::string user{"Bhsdns"},channel{"##chat"};
	unsigned int port = 6667;
    
    Channel chan(channel);
    User usr(user); 
    string msg;
    
	Bot *bot = new Bot(server,channel,nick,user,pass,port);
	bot->Connect();
         
    bot->Disconnect();
	cout<<"Exiting program now."<<endl;
	delete bot;
	return 0;
}
