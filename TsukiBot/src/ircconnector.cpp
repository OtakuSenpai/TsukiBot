#include "ircconnector.hpp"
#include <iostream>
#include <string>
#include <algorithm>

Tsuki :: IRCConnector :: IRCConnector(const std::string& server,const unsigned int& port)
{
  try {
    tcpsock = 0;
    buffer = new char[buf_size];

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
      //const char* error = SDLNet_GetError();
      std::string s = static_cast<std::string>("ircconnector.cpp : In Tsuki::IRCConnector::IRCConnector(std::string,unsigned int) : Error in initializing SDL. Error is  ") + std::string(SDLNet_GetError()) + std::string(".\n");
      throw  std::runtime_error(s);
    }
    if(SDLNet_Init() == -1) {
      //const char* error = SDLNet_GetError();
      std::string s = "ircconnector.cpp : In Tsuki::IRCConnector::IRCConnector(std::string,unsigned int) : Error in initializing SDL. Error is  " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
    if (SDLNet_ResolveHost(&ipaddress,server.c_str(),port) < 0) {
      std::string s = "ircconnector.cpp : In Tsuki::IRCConnector::IRCConnector(std::string,unsigned int). Error in initializing SDL. Error is  " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
      ipaddress.host = 0;
      ipaddress.port = 0;
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

Tsuki :: IRCConnector :: ~IRCConnector() {
  delete buffer; buffer = nullptr;
  if(!(tcpsock == 0)) {
    SDLNet_TCP_Close(tcpsock);
  }
  SDLNet_Quit();
  SDL_Quit();
}

void  Tsuki :: IRCConnector :: Connect()
{
  try {
    if((ipaddress.host == 0) && (ipaddress.port == 0)) {
      std::string s = "ircconnector.cpp : In Tsuki::IRCConnector::Connect(). Empty IRCConnector::ipaddress. Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
    tcpsock =  SDLNet_TCP_Open(&ipaddress);
    if(!tcpsock) {
      std::string s = "ircconnector.cpp : In Tsuki::IRCConnector::Connect(). Empty IRCConnector::ipaddress.  Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
    else { connected = true; }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: IRCConnector :: SendData(const IRCMessage& data)
{
  try {
    int len,ret;
    std::string msg,temp = data.getData();
    if(temp.size() >= 512) {
    msg = temp.substr(0,512);
    }
    else { msg = temp; }
    len = msg.size();
    ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);
    if(ret<len) {
      std::string s = "ircconnector.cpp : In Tsuki::IRCConnector::SendData(IRCMessage&). Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: IRCConnector :: SendData(const char* data)
{
  try {
    int len,ret;
    std::string temp{data},msg;
    if(temp.size() >= 512) {
    msg = temp.substr(0,512);
    }
    else { msg = temp; }
    len = msg.size();
    ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);
    if(ret<len) {
      std::string s = "ircconnector.cpp: In Tsuki::IRCConnector::SendData(const char*). Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}


void Tsuki :: IRCConnector :: SendData(const std::string& data)
{
  try {
    int len,ret;
    std::string msg;
    if(data.size() >= 512) {
      msg = data.substr(0,512);
    }
    else { msg = data; }
    len = msg.size();
    ret = SDLNet_TCP_Send(tcpsock,msg.c_str(),len);

    if(ret<len) {
      std::string s = "ircconnector.cpp: In Tsuki::IRCConnector::SendData(std::string&). Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
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
  std::string message,s;
  try {
    int ret;
    std::fill(buffer,buffer+2048,0);
    ret = SDLNet_TCP_Recv(tcpsock,reinterpret_cast<void*>(buffer),buf_size);
    if(ret <= 0) {
      std::string s = "ircconnector.cpp: In Tsuki::IRCConnector::RecvData(). Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
    message.assign(buffer);
    // Check if the input received is demarcated by a newline
    if (message.at(message.size() - 1) != '\n') {
      // std::cout << "Receiving more data!" << std::endl;
      s = RecvData();
      message = message + s; s.clear();
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
  return message;
}

// Can't const it due to a weird error
bool Tsuki :: IRCConnector :: RecvData(std::string& msg)
{
  bool hasit = false;
  std::string s;
  std::fill(buffer,buffer+2048,0);
  try {
    int ret;
    ret = SDLNet_TCP_Recv(tcpsock,reinterpret_cast<void*>(buffer),buf_size);
    if(ret<=0) {
      std::string s = "ircconnector.cpp: In Tsuki::IRCConnector::RecvData(std::string&). Error is " + std::string(SDLNet_GetError()) + ".\n";
      throw std::runtime_error(s);
    }
    else { hasit =true; }
    msg.assign(buffer);
    while(msg.at(msg.size() - 1) != '\n') {
      s = RecvData();
      msg = msg + s; s.clear();
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
  return hasit;
}
