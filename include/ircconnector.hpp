#ifndef IRCCONNECTOR_HPP
#define IRCCONNECTOR_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"

#include "ircmessage.hpp"

using namespace Tsuki;

namespace Tsuki
{
	
   class IRCConnector
   {
   	  private:
		 IPaddress ipaddress;
		 TCPsocket tcpsock;
		 char* buffer;
		 const int buf_size =2048; 
         bool connected = false; 
          
	  public: 
	  IRCConnector(std::string& server,unsigned int port); 
	  ~IRCConnector()
	  {
	     delete buffer;
	     if(!(tcpsock == 0))
         {
            SDLNet_TCP_Close(tcpsock);
         }                 
         SDLNet_Quit();
		 SDL_Quit();
	  }
	   
	  TCPsocket RetTCPsocket() { return tcpsock; }
	  bool isConnected() { return connected; }
	  char* RetBuffer() { return buffer; }
	  
	  //Connect to a server by using the Join_Data variable
	  void Connect();
			
	  //Disconnect from the server
	  void DisConnect() { SDLNet_TCP_Close(tcpsock); } 
                        
	  //Send Data to the server
	  void SendData(const char* data);
	  void SendData(std::string& data);
	  void SendData(IRCMessage& data);
			
	  //Receive data from the server
	  std::string RecvData();
	  bool RecvData(std::string& message);				
	};

}

#endif
