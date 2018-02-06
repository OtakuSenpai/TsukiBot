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

#include "irchelpers.hpp"
#include <iostream>

void Tsuki :: JoinChannel(const Channel& chan,Tsuki::IRCConnector& conn) {
  std::string data = std::string{"JOIN "} + chan.getData() + std::string{"\r\n"};
  conn.SendData(data);
}

void Tsuki :: JoinChannel(const std::string& channel,Tsuki::IRCConnector& conn) {
  std::string data = std::string{"JOIN "} + channel + std::string{"\r\n"};
  conn.SendData(data);
}

void Tsuki :: SendMsg(const std::string& msg,Tsuki::IRCConnector& conn) {
  conn.SendData(msg);
}

void Tsuki :: SendMsg(const char* command,const std::string& msg
                      ,Tsuki::IRCConnector& conn) {
  std::string s = std::string(command) + " :" + msg;
  conn.SendData(s);
}

void Tsuki :: SendMsg(const std::string& command,const std::string& msg
                      ,Tsuki::IRCConnector& conn) {
  std::string s = command + " :" + msg;
  conn.SendData(s);
}


void Tsuki :: SendNick(std::string& bot_name,Tsuki::IRCConnector& conn) {
  std::string s;
  s = "NICK " + bot_name + "\r\n";
  std::cout<<"Nick: "<<s<<std::endl;
  conn.SendData(s);
}

void Tsuki :: SendNick(const std::string& nick,Tsuki::IRCConnector& conn) {
  std::string s;
  s = "NICK " + nick + "\r\n";
  conn.SendData(s);
}

void Tsuki :: SendUser(const User& user,const std::string& realname
                       ,const int& mode,Tsuki::IRCConnector& conn) {
  std::string s = "USER " + user.getData() + " " + std::to_string(mode) +
                  " * :" + realname + "\r\n";
  conn.SendData(s);
}

void Tsuki :: SendUser(const User& user,const char* realname,const int& mode
                       ,Tsuki::IRCConnector& conn) {
  std::string s = "USER " + user.getData() + " " + std::to_string(mode) +
                  " *" + " :" + std::string(realname) + "\r\n";
  conn.SendData(s);
}

void Tsuki :: SendMe(const std::string& message,const std::string& target
                     ,Tsuki::IRCConnector& conn) {
  std::string temp = "PRIVMSG " + target + " :\001ACTION " + message + "\001\r\n";
  std::cout<<std::endl<<std::endl<<std::endl<<"Sending /me : "
           <<temp<<std::endl<<std::endl<<std::endl;
  conn.SendData(temp);
}

void Tsuki :: SendPrivMsg(const std::string& target,const std::string& msg
                          ,Tsuki::IRCConnector& conn) {
  std::string temp = "PRIVMSG " + target + " :" + msg + "\r\n";
  std::cout<<"Retvalue: "<<temp<<"\n";
  SendMsg(temp,conn);
}

void Tsuki :: SendPong(const std::string& contents,Tsuki::IRCConnector& conn) {
  std::string temp = "PONG " + contents + "\r\n";
  conn.SendData(temp);
}

void Tsuki :: SendPart(const std::string& channel,Tsuki::IRCConnector& conn) {
  std::string temp = "PART " + channel + "\r\n";
  conn.SendData(temp);
}

void Tsuki :: SendPart(const std::string& channel,const std::string& message
                       ,Tsuki::IRCConnector& conn) {
  std::string temp = "PART " + channel + " :" + message + "\r\n";
  std::cout<<"\nSending part message: "<<temp<<std::endl;
  conn.SendData(temp);
}
