#include "ircconnector.hpp"
#include <iostream>

Tsuki :: IRCConnector :: IRCConnector(std::string& server,unsigned int port)
{
   tcpsock = 0;
   buffer = new char[buf_size];
        
   if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
   {
	  //const char* error = SDLNet_GetError(); 
	  std::string s = static_cast<std::string>("ZenIRC Error: In Zen :: IRCConnector :: IRCConnector(std::string,unsigned int). Error in initializing SDL. Error is  ") + std::string(SDLNet_GetError()) + std::string(" ."); 
      throw  std::runtime_error{s};	
   }
   if(SDLNet_Init() == -1)
   {
	  //const char* error = SDLNet_GetError(); 
      std::string s = static_cast<std::string>("ZenIRC Error: In Zen :: IRCConnector :: IRCConnector(std::string,unsigned int). Error in initializing SDL. Error is  ") + std::string(SDLNet_GetError()) + std::string(" .");
	  throw std::runtime_error{s};
   }
   if (SDLNet_ResolveHost(&ipaddress,server.c_str(),port) < 0) 
   {
	  const char* error = SDLNet_GetError(); 
	  std::string s = static_cast<std::string>("ZenIRC Error: In Zen :: IRCConnector :: IRCConnector(std::string,unsigned int). Error in initializing SDL. Error is  " + std::string(error) + " ."); 	
      throw std::runtime_error{s};
      ipaddress.host = 0;
      ipaddress.port = 0;
   }
}

void  Tsuki :: IRCConnector :: Connect()
{
   if((ipaddress.host == 0) && (ipaddress.port == 0))
   {   
	  const char* error = SDLNet_GetError(); 
      std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: Connect().Empty IRCConnector :: ipaddress. Error is " + std::string(error) + " .");	
      throw std::runtime_error{s};
   }
   tcpsock =  SDLNet_TCP_Open(&ipaddress);
   if(!tcpsock)
   {
	  const char* error = SDLNet_GetError(); 	
      std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: Connect().Empty IRCConnector :: ipaddress. Error is " + std::string(error) + " .");	
      throw std::runtime_error{s};  
   }
   else { connected = true; }
}	

void Tsuki :: IRCConnector :: SendData(IRCMessage& data)
{
   int len,ret;
   std::string msg,temp = ":" + data.RetMsgData().RetPrefix() + " " + data.RetMsgData().RetCommand() + " " + data.RetMsgData().RetSParameters();
   if(temp.size() >= 512)
   {
	  msg = temp.substr(0,512);
   }
   else { msg = temp; }
   len = msg.size();
   ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);
   if(ret<len)
   {
	  const char* error = SDLNet_GetError(); 
	  std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: SendData(IRCMessage&). Error is " + std::string(error) + " ."); 
      throw std::runtime_error{s};
   }
}		

void Tsuki :: IRCConnector :: SendData(const char* data)
{
   int len,ret;
   std::string temp{data},msg;
   if(temp.size() >= 512)
   {
	  msg = temp.substr(0,512);
   }
   else
   {
	  msg = temp;
   }   
   len = msg.size();
   ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);
   if(ret<len)
   {
      const char* error = SDLNet_GetError();
      std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: SendData(const char*). Error is " + std::string(error) + " .");
	  throw std::runtime_error{s};
   }
}


void Tsuki :: IRCConnector :: SendData(std::string& data)
{
   int len,ret;
   std::string msg;
   if(data.size() > 512)
   {
	  msg = data.substr(0,512);
   }
   else
   {
	  msg = data;
   } 
   //std::cout<<"Sending data: "<<msg.c_str()<<std::endl;
   len = msg.size();
   ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);
	
   if(ret<len)
   {
	  const char* error = SDLNet_GetError(); 
      std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: SendData(std::string&). Error is " + std::string(error) + " .");
	  throw std::runtime_error{s};
   }
}

/*void Zen :: IRCConnector :: RecvData() 	
{
	int ret;
	ret = SDLNet_TCP_Recv(tcpsock,&buffer,buf_size);
	if(ret <= 0)
	{
		std::string s = "ZenIRC Error: Error in Zen :: IRCConnector :: RecvData(). Error is " + std::string(SDLNet_GetError()) + " .";
		throw std::runtime_error{s};
		DisConnect();
	}
}*/

std::string Tsuki :: IRCConnector :: RecvData() 	
{
	int ret;
	
	ret = SDLNet_TCP_Recv(tcpsock,reinterpret_cast<void*>(buffer),buf_size);
	if(ret <= 0)
	{
		const char* error = SDLNet_GetError();
		std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: RecvData(). Error is " + std::string(error) + " .");
		throw std::runtime_error{s};
	}
	std::string message(buffer);
	//std::cout<<"Receiving: "<<message<<std::endl;
	return message;
}

bool Tsuki :: IRCConnector :: RecvData(std::string& msg)
{
	int ret;
	bool hasit = false;
	ret = SDLNet_TCP_Recv(tcpsock,buffer,buf_size);
    if(ret<=0)
    {
	   const char* error = SDLNet_GetError();	
       std::string s = static_cast<std::string>("ZenIRC Error: Error in Zen :: IRCConnector :: RecvData(std::string&). Error is " + std::string(error) + " .");
	   throw std::runtime_error{s};
    }
    else { hasit =true; }
    msg.assign(buffer);
    //std::cout<<msg<<std::endl;
    return hasit;
}

         
