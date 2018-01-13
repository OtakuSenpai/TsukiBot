#include "TsukiIRC.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <chrono>
#include <thread>

using namespace Tryx;

void Tsuki :: Bot :: setName(const std::string& name)
{
  bot_name = name;
  server_data.setNick(bot_name);
}

std::string Tsuki :: Bot :: get_text_after_command(const std::string& message,const char* command)
{
  std::string temp;
  std::string comm{command};
  temp = message.substr(comm.size());
  return temp;
}

bool Tsuki :: Bot :: has_in_chan(const std::string& name,const std::string& channel)
{
  bool has_it = false;
  for(auto&& i: chan_list) {
    if(channel == i.getData()) {
      for(auto&& j: i.getUserList()) {
        if(name == j.getData()) { has_it = true; break; }
        else if(name == j.getData().substr(1)) { has_it = true; break; }
      }
      if(has_it) { break; }
    }
    else continue;
  }
  std::cout<<std::endl<<"Has_in_chan: "<<has_it<<std::endl<<std::endl;
  return has_it;
}

void Tsuki :: Bot :: handle_msg(std::string& message)
{
  try {  
    std::cout<<std::endl<<"Server Data: "<<message<<std::endl<<std::endl;
    segragrator(message, "\r\n"); // separate whole messages
    //std::cout<<std::endl<<"Size of chan_list: "<<chan_list.size()<<std::endl<<std::endl;
    
    message.clear();
    msglogs.clear();

  }  
  catch(std::exception& e){
    std::cout<<"Caught exception: \n"<<e.what(); 
  }
}

std::vector<Tsuki::Nick> Tsuki :: Bot :: get_user_list(const std::string& from)
{
  std::vector<Tsuki::Nick> nick_list;
  bool isthere = false;
  for(auto&& i = std::begin(chan_list); i != std::end(chan_list); i++) {
    if(i->getData() == from) {
      nick_list = i->getUserList();
      isthere = true;
      std::cout<<std::endl<<"Found channel: "<<i->getData()<<std::endl<<std::endl;
      if(isthere) break;
    }
  }
  return nick_list;
}

void Tsuki :: Bot :: segragrator(const std::string& message,const char* data)
{
  size_t pos = 0;
  std::string token,delimiter{data},tempValue = message;
  Tsuki::IRCMessage temp;

  while ((pos = tempValue.find(delimiter)) != std::string::npos) {
    token = tempValue.substr(0, pos);
    temp.Parse(token);
    msglogs.push_back(temp); temp.clear(); token.clear();
    tempValue.erase(0, pos + delimiter.length());
  }
}

void Tsuki :: Bot :: SetConn() {
  conn.DisConnect();
  conn.Connect();

  while(!conn.isConnected()) {
    std::cerr<<"Unable to connect to server!!! Retrying..."<<std::endl;
    std::this_thread::sleep_for(wait_time);
    conn.Connect();
    setConnected(true);
  }
  setState(Tsuki::ServerState::SETTING_NICK);

  if(getState() == Tsuki::ServerState::SETTING_NICK) {
    SendNick();
    std::cout<<"Nick sent..."<<std::endl;
    setState(Tsuki::ServerState::SETTING_USER);
  }
  if(getState() == Tsuki::ServerState::SETTING_USER) {
    std::cout<<"Sending user..."<<std::endl;
    SendUser(server_data.getUser(),server_data.getRealName(),0);
    std::cout<<"User sent..."<<std::endl;
    setState(Tsuki::ServerState::SETTING_PONG);
    setRunning(true);
  }
}

void Tsuki :: Bot :: Connect()
{
  try {	
    std::string contents,command{"PING"};
    std::string serv_data;
    running = false;

    while(!isConnected() && !isRunning()) {
      std::this_thread::sleep_for(wait_time);
      SetConn();
    }
  
    std::cout<<"Entering loop...\n";
    while(conn.RecvData(serv_data) && isRunning()) { 
      if(begins_with(serv_data,"PING")) {
        if(contents == "") contents = serv_data.substr(command.size());
        SendPong(contents);
        setState(Tsuki::ServerState::WORKING); setConnected(true);
      }
      if(has_it(serv_data,"004")) {
        std::cout<<std::endl<<"Connected!!!"<<std::endl<<std::endl;
        setConnected(true);
      }
      if(has_it(serv_data,"433")) {
        SendNick(second_name);
      }
      if(connected == true && joined == false) {
        JoinChannel(server_data.getChannel()); joined = true;
      }
      if(getState() == Tsuki::ServerState::SETTING_PONG || begins_with(serv_data,"PING")) {
        if(contents == "") contents = serv_data.substr(command.size());
        SendPong(contents);
        setState(Tsuki::ServerState::WORKING);
      }
      
      //:nick!user@host QUIT :Ping timeout: 200 seconds
      if(has_it(serv_data,":Ping timeout:") &&   
        ((has_it(serv_data,bot_name.c_str())) || (has_it(serv_data,second_name.c_str()))) &&
        has_it(serv_data,"QUIT")) {
		setState(Tsuki::ServerState::NOT_CONNECTED);
		setRunning(false);
		setConnected(false);
		while(!isConnected() && !isRunning()) {
          std::this_thread::sleep_for(wait_time);
          SetConn();
        }
	  }	
      handle_msg(serv_data);
      serv_data.clear();
    }
    std::cout<<"Exiting Tsuki::Bot::Connect....\n";
  }
  catch(std::exception& e) { 
	std::cerr<<"Caught exception: \n"<<e.what();
	conn.DisConnect();
	std::exit(EXIT_FAILURE);
  }   
}

void Tsuki :: Bot :: Disconnect()
{
  conn.DisConnect();
  setState(Tsuki::ServerState::NOT_CONNECTED);
}

void Tsuki :: Bot :: JoinChannel(const Channel& chan)
{
  std::string data = std::string{"JOIN "} + chan.getData() + std::string{"\r\n"};
  conn.SendData(data);
}

void Tsuki :: Bot :: JoinChannel(const std::string& channel)
{
  std::string data = std::string{"JOIN "} + channel + std::string{"\r\n"};
  conn.SendData(data);
}

void Tsuki :: Bot :: SendMsg(const std::string& msg)
{
  conn.SendData(msg);
}

void Tsuki :: Bot :: SendMsg(const char* command,const std::string& msg)
{
  std::string s = std::string(command) + " :" + msg;
  conn.SendData(s);
}

void Tsuki :: Bot :: SendMsg(const std::string& command,const std::string& msg)
{
  std::string s = command + " :" + msg;
  conn.SendData(s);
}


void Tsuki :: Bot :: SendNick()
{
  std::string s;
  s = "NICK " + bot_name + "\r\n";
  std::cout<<"Nick: "<<s<<std::endl;
  conn.SendData(s);
}

void Tsuki :: Bot :: SendNick(const std::string& nick)
{
  std::string s;
  s = "NICK " + nick + "\r\n";
  conn.SendData(s);
}

void Tsuki :: Bot :: SendUser(const User& user,const std::string& realname,const int& mode)
{
  std::string s = "USER " + user.getData() + " " + std::to_string(mode) + " * :" + realname + "\r\n";
  conn.SendData(s);
}

void Tsuki :: Bot :: SendUser(const User& user,const char* realname,const int& mode)
{
  std::string s = "USER " + user.getData() + " " + std::to_string(mode) + " *" + " :" + std::string(realname) + "\r\n";
  std::cout<<"Sending user: "<<s<<std::endl;
  conn.SendData(s);
}

void Tsuki :: Bot :: SendMe(const std::string& message,const std::string& target)
{
  std::string temp = "PRIVMSG " + target + " :\001ACTION " + message + "\001\r\n";
  std::cout<<std::endl<<std::endl<<std::endl<<"Sending /me : "<<temp<<std::endl<<std::endl<<std::endl;
  conn.SendData(temp);
}

void Tsuki :: Bot :: SendPrivMsg(const std::string& target,const std::string& msg) {
  std::string temp = "PRIVMSG " + target + " :" + msg + "\r\n";
  std::cout<<"Retvalue: "<<temp<<"\n"; 
  SendMsg(temp);
}

void Tsuki :: Bot :: SendPong(const std::string& contents)
{
  std::string temp = "PONG " + contents + "\r\n";
  conn.SendData(temp);
}

void Tsuki :: Bot :: SendPart(const std::string& channel)
{
  std::string temp = "PART " + channel + "\r\n";
  conn.SendData(temp);
}

void Tsuki :: Bot :: SendPart(const std::string& channel,const std::string& message)
{
  std::string temp = "PART " + channel + " :" + message + "\r\n";
  std::cout<<"\nSending part message: "<<temp<<std::endl;
  conn.SendData(temp);
}

void Tsuki :: Bot :: AddChannel(const std::string& channel,const std::string& command)
{
  size_t j = chan_list.size();
  bool has_chan = false,chan_is_not_command = false;
  std::string from = channel;
  if(j == 0 ) {
    if(command == "372" || command == "NOTICE" || from == "#freenode" || from == "##Linux" || command != "PRIVMSG")
    { from = ""; chan_is_not_command = true; }
    else
    { Tsuki::Channel a{from}; chan_list.push_back(a); from = ""; }
  }
  else if(j > 0) {
    if(command == "372" || command == "NOTICE" || from == "#freenode" ||  command != "PRIVMSG")
    { from = ""; chan_is_not_command = true; }
    for(auto i = std::begin(chan_list); i != std::end(chan_list); i++) {
      size_t k = std::distance(std::begin(chan_list),i);
      if(k > j) break;
      if(i->getData() == from)
      { has_chan = true; }
    }
    if(!has_chan) {
      if(!chan_is_not_command)
      { Tsuki::Channel a{from}; chan_list.push_back(a); }
    }
  }
}

void Tsuki :: Bot :: LoadPlugin(const std::string& path) {
  kernel.loadPlugin(path);
}

void Tsuki :: Bot :: LoadPlugins(const std::string& path) {
  kernel.loadPlugins(path,true);
}
