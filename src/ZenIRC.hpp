#ifndef  ZENIRC_HPP
#define ZENIRC_HPP

#include <deque>
#include <string>
#include <iterator>

#include "ircconnector.hpp"

using namespace Tsuki;

namespace Tsuki
{
class Bot
{
         
   protected:
      bool running;
	  IRCConnector conn;
	  Join_Data server_data;
	  std::vector<Channel> chan_list;
      //std::deque<IRCMessage> msglogs;
	  std::string BotName;
	  ServerState state;
	  
	  bool begins_with(std::string& message,const char* command);
	  bool has_it(std::string& data,const char* command);
      std::string get_text_after_command(std::string& message,const char* command);
      virtual void handle_msg(std::string& msg);
      void GetState(ServerState s) { state = s; }
            
   public:
      Bot(std::string& server,unsigned int port=6667) : conn{server,port}, BotName{} {}
      Bot(std::string& server,std::string& channel,
          std::string& nick,std::string& user,
          std::string& password,
          unsigned int& port)  : conn{server,port}, server_data{server,channel,nick,user,password,port}, 
                                 BotName{} { GetName(nick); }
      virtual ~Bot() {}
			
	  void GetName(std::string& name);
	  ServerState RetState() { return state; }
	  bool IsRunning() { return running; }
		 
	   
	  //Connect to the server
      virtual void Connect();
			
	  //Disconnect
	  void Disconnect();
			
      //Join a channel
      void JoinChannel(Channel& chan); 
      void JoinChannel(std::string& channel);

	  //Send a normal message Message
	  void SendMsg(std::string& msg);
      void SendMsg(const char* command,std::string& message);
                        
      //Send NICK message
      void SendNick();
      void SendNick(std::string& nick); 
                        
      //Send USER message
      void SendUser(User user,std::string& realname,int mode);
      void SendUser(User user,const char* realname,int mode);
      
      //Me message
      void SendMe(std::string& message);
      
      //Send PONG message
      void SendPong(std::string& contents);		
      
      //Add a channel
	  void AddChannel(std::string& channel);
};
			
			
}		
                       

#endif
		
			
