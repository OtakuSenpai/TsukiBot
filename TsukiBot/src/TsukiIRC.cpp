///////////////////////////////////////////////////////////////////////////////////
// TsukiBot IRC Bot made by Avra Neel Chakraborty                                //
//                                                                               //
// Copyright (c) 2018 Avra Neel Chakraborty                                      //
//                                                                               //
// This Source Code Form is subject to the terms of the Mozilla Public           //
// License, v. 2.0. If a copy of the MPL was not distributed with this           //
// file, You can obtain one at http://mozilla.org/MPL/2.0/.                      //
//                                                                               //
// The above copyright notice and this permission notice shall be included in    //
// all copies or substantial portions of the Software.                           //
///////////////////////////////////////////////////////////////////////////////////

#include "TsukiIRC.hpp"

#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <chrono>
#include <thread>

void Tsuki :: Bot :: setName(const std::string& name) {
  bot_name = name;
  server_data.setNick(bot_name);
}

std::string Tsuki :: Bot :: get_text_after_command(const std::string& message,const char* command) {
  std::string temp;
  std::string comm{command};
  temp = message.substr(comm.size());
  return temp;
}

bool Tsuki :: Bot :: has_in_chan(const std::string& name,const std::string& channel) {
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
  return has_it;
}

void Tsuki :: Bot  :: handleNickList(IRCMessage& temp) {
  std::string total;
  Tsuki::Channel channel;
  if(temp.getPacketInfo() != PacketType::RPL_ENDOFNAMES) { return; }
  else if(temp.getPacketInfo() == PacketType::RPL_NAMREPLY) {
    channel =  temp.getContent().substr(0,temp.getContent().find(" "));
    total = total + temp.getContent().substr(temp.getContent().find(":"));
    for(auto&& i : chan_list) {
      if(i == channel) {
        i.setUsers(total);
      }
    }
  }
}


void Tsuki :: Bot :: handle_msg(std::string& message) {
  try {
    std::cout<<std::endl<<"Server Data: "<<message<<std::endl<<std::endl;
    std::vector<IRCMessage> tempMsgs; segragrator(message, "\r\n",tempMsgs); // separate whole messages
    std::cout<<"Messages received: "<<msglogs.size()<<std::endl;
    for(auto&& i: tempMsgs) {
      if(i.getType() != Type::special && i.getType() != Type::join &&
         i.getType() != Type::ping && i.getType() != Type::notice) {

        std::string tempContent = i.getContent().substr(1);
        if(has_it(tempContent,std::string(specialChar + "join"))) {
          std::string temp = i.getContent().substr(i.getContent().find(" ")+1);
          Join(temp);
        }
        if(has_it(tempContent,std::string(specialChar + "part"))) {
          // $part ##llamas
          // $part ##llamas bye
          //Content: :$part ##llamas

          Part(tempContent);
        }
        if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_NAMREPLY))) ||
                has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_TOPIC)))) {

          if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_TOPIC)))) {
            Topic(tempContent);
          }
          else if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_NAMREPLY)))) {
            Namelist(tempContent);
          }
        }
        if(has_it(tempContent,std::string(specialChar + "quit"))) {
          Disconnect(); disconnect = true; break;
        }
        std::cout<<"TempContent: "<<tempContent<<std::endl;

        //Automatic Plugin loading part
        if(hasTrigger(tempContent,specialChar,pluginSubStrs)) {
          std::string temp = tempContent;
          temp = temp.substr(1);
          std::cout<<"Temp: "<<temp<<std::endl;
          for(auto&& k: pluginSubStrs) {
            if(temp.substr(0,temp.find(" ")) == k.first) {
              std::string name = kernel.getPluginName(findPlugin(k.first));
              std::cout<<"Name: "<<name<<std::endl;
              BasePlugin* p = kernel.getFuncHandle(name);
              std::cout<<"Loaded plugin: "<<((p == nullptr) ? true : false)<<std::endl;
              if(p != nullptr) {
                std::string retStr = p->onCommand("onCall",temp.c_str());
                std::cout<<"RetStr: "<<retStr<<std::endl;
                SendPrivMsg(i.getSender(),retStr,conn);
                delete p;
              }
              else if(p == nullptr) {
                SendMsg("Plugin not found!!!",conn);
              }
            }
          }
        }

      }
    }

    // Move the messages from the temp storage to msglogs
    msglogs.resize(tempMsgs.size() + msglogs.size());
    std::move_backward(tempMsgs.begin(), tempMsgs.end(), msglogs.end());

    if(msglogs.size() > 5000) { makeSpace(msglogs); }
    message.clear();
  }
  catch(std::exception& e){
    std::cout<<"Caught exception: \n"<<e.what()<<std::endl
             <<"Data is: "<<message<<std::endl;
  }
}

std::vector<Tsuki::Nick> Tsuki :: Bot :: get_user_list(const std::string& from) {
  std::vector<Tsuki::Nick> nick_list;
  bool isthere = false;
  for(auto&& i = std::begin(chan_list); i != std::end(chan_list); i++) {
    if(i->getData() == from) {
      nick_list = i->getUserList();
      isthere = true;
      if(isthere) break;
    }
  }
  return nick_list;
}

void Tsuki :: Bot :: segragrator(const std::string& message,const char* data,
                                std::vector<Tsuki::IRCMessage>& msg) {
  size_t pos = 0;
  std::string token,delimiter{data},tempValue = message;

  while ((pos = tempValue.find(delimiter)) != std::string::npos) {
    token = tempValue.substr(0, pos);
    Tsuki::IRCMessage temp(token);
    msg.push_back(temp); temp.clear(); token.clear();
    tempValue.erase(0, pos + delimiter.length());
  }
}

void Tsuki :: Bot :: SetConn() {
  conn.DisConnect();
  conn.Connect();

  while(isConnected() == false) {
    std::cerr<<"Unable to connect to server!!! Retrying..."<<std::endl;
    std::this_thread::sleep_for(wait_time);
    conn.Connect();
    setConnected(conn.isConnected());
  }
  setState(Tsuki::ServerState::SETTING_NICK);

  if(getState() == Tsuki::ServerState::SETTING_NICK) {
    std::cout<<"Sending nick..."<<std::endl;
    SendNick(bot_name,conn);
    std::cout<<"Nick sent..."<<std::endl;
    setState(Tsuki::ServerState::SETTING_USER);
  }
  if(getState() == Tsuki::ServerState::SETTING_USER) {
    std::cout<<"Sending user..."<<std::endl;
    SendUser(server_data.getUser(),server_data.getRealName(),0,conn);
    std::cout<<"User sent..."<<std::endl;
    setState(Tsuki::ServerState::SETTING_PONG);
    setRunning(true);
  }
}

void Tsuki :: Bot :: Connect() {
  try {
    std::string contents,command{"PING"};
    std::string serv_data;
    running = false;
    disconnect = false;

    while(!isConnected() && !isRunning()) {
      SetConn();
    }

    std::cout<<"Entering loop...\n";
    while(conn.RecvData(serv_data) && isRunning() && !disconnect) {
      if(begins_with(serv_data,"PING")) {
        if(contents == "") contents = serv_data.substr(command.size());
        SendPong(contents,conn);
        setState(Tsuki::ServerState::WORKING); setConnected(true);
      }
      if(has_it(serv_data,"004")) {
        std::cout<<std::endl<<"Connected!!!"<<std::endl<<std::endl;
        setConnected(true);
      }
      if(has_it(serv_data,"433")) {
        SendNick(second_name,conn);
      }
      if(connected == true && joined == false) {
        JoinChannel(server_data.getChannel(),conn); joined = true;
      }
      if(getState() == Tsuki::ServerState::SETTING_PONG || begins_with(serv_data,"PING")) {
        if(contents == "") contents = serv_data.substr(command.size());
        SendPong(contents,conn);
        setState(Tsuki::ServerState::WORKING);
      }

      //
      if(serv_data.find(":Ping timeout:",0) != std::string::npos &&
        (has_it(serv_data,bot_name.c_str()) || has_it(serv_data,second_name.c_str()))) {
        setState(Tsuki::ServerState::NOT_CONNECTED);
        conn.DisConnect();
        setRunning(false);
        setConnected(false);
        while(!isConnected() && !isRunning()) {
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

void Tsuki :: Bot :: Disconnect() {
  conn.DisConnect();
  setRunning(false);
  setConnected(false);
  setState(Tsuki::ServerState::NOT_CONNECTED);
}

void Tsuki :: Bot :: LoadPlugin(const std::string& path) {
  kernel.loadPlugin(path);
}

void Tsuki :: Bot :: LoadPlugins(const std::string& path) {
  kernel.loadPlugins(path,true);
  std::string name,subtrigger,trigger;
  std::vector<std::string> subTrigs;
  BasePlugin *p = nullptr;
  size_t i;

  for(i = 0; i<kernel.getPlugins().size(); ++i) {
    name = kernel.getPluginName(i);
    std::cout<<"Plugin name: "<<name<<std::endl;
    p = kernel.getFuncHandle(name);
    subtrigger = p->onCommand("getSubTriggers","");
    std::cout<<"Subtriggers: "<<subtrigger<<std::endl;
    std::stringstream s(subtrigger);
    for(std::string temp; std::getline(s,temp,' '); ) {
      subTrigs.push_back(temp);
    }
    trigger = p->onCommand("getTrigStr","");
    std::cout<<"Trigger: "<<trigger<<std::endl<<std::endl;
    pluginSubStrs.emplace(trigger,subTrigs);
    trigger.clear(); subtrigger.clear();
    name.clear(); subTrigs.clear();
    delete p;
  }
  std::cout<<"Loaded: "<<i<<" plugins!"<<std::endl;

  i = 0;
  size_t k;
  for(auto&& j: pluginSubStrs) {
    for(k = 0; k<j.second.size(); ++k);
    i = i + k;
  }
  std::cout<<"Loaded: "<<i<<" subplugins!"<<std::endl;
}

size_t Tsuki :: Bot :: findPlugin(const std::string& trig) {
  BasePlugin* p = nullptr;
  std::string name;
  size_t pos = -1;

  for(size_t i = 0; i<kernel.getPlugins().size(); ++i) {
    name = kernel.getPluginName(i);
    p = kernel.getFuncHandle(name);
    std::string temp = p->onCommand("getTrigStr","");
    std::cout<<"Trig: "<<trig<<std::endl;
    std::cout<<"Trig from plugin: "<<temp<<std::endl;
    if(trig == temp) {
      std::cout<<"Found!"<<std::endl;
      pos = i;
      std::cout<<"Pos: "<<pos<<std::endl;
      break;
    }
    else {
      delete p;
      name.clear();
      continue;
    }
  }
  return pos;
}

BasePlugin* Tsuki :: Bot :: retPlugin(const size_t& pos) {
  Plugin::PluginFactoryFunc temp;
  size_t j = 0;
  for(auto&& i: kernel.getPlugins()) {
	if(pos == j)
	  temp = i.second.get()->getFuncHandle();
	++j;
  }  
  
  BasePlugin* p = reinterpret_cast<BasePlugin*>(temp());

  if(p != nullptr) {
    std::cout<<"returning plugin!!\n";
    return p;
  }
  else return nullptr;
}

void Tsuki :: Bot :: makeSpace(std::vector<IRCMessage> msgs) {
  std::move(msgs.begin() + 3000, msgs.end(),msgs.begin());
  msgs.resize(2000);
}

void Tsuki :: Bot :: Join(std::string& temp) {
  JoinChannel(temp,conn);
  chan_list.push_back(Tsuki::Channel(temp));
}

void Tsuki :: Bot :: Part(std::string& tempContent) {
  std::string total,chan,message;
  size_t pos1 = -1;

  total = tempContent.substr(total.find(" ")+1);
  if(total.at(0) == ' ') { total = total.substr(1); }
  total = tempContent.substr(total.find(" ")+1);

  if(has_it(total,' ')) {
    chan = total.substr(0,total.find(' '));
    total = total.substr(total.find_first_of(' ')+1);
    message = total;
  }
  else { chan = total; }

  if(message.empty()) { SendPart(chan,conn); }
  else if(!message.empty()) { SendPart(chan,message,conn); }

  for(auto&& j: chan_list) {
    ++pos1;
    if(j.getData() == chan) {
      chan_list.erase(chan_list.begin() + pos1);
      break;
    }
  }
}

void Tsuki :: Bot :: Namelist(std::string& tempContent) {
  //:cherryh.freenode.net 353 G33kb0i = #tsukibot :G33kb0i OtakuSenpai
  std::string tempChan = tempContent.substr(0,tempContent.find(" "));
  std::string nameList = tempContent.substr(tempContent.find(":"));

  for(auto j: chan_list) {
    if(j.getData() == tempChan) {
      j.setUsers(nameList); break;
    }
  }
}
void Tsuki :: Bot :: Topic(std::string& tempContent) {
  //:cherryh.freenode.net 332 G33kb0i ##llamas :The official #1 off-topic

  std::string chan = tempContent.substr(0,tempContent.find(" "));
  std::string topic = tempContent.substr(tempContent.find(":"));
  for(auto j: chan_list) {
    if(j.getData() == chan) { j.setTopic(topic); break; }
  }
}
