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

#ifndef IRCHELPERS_HPP
#define IRCHELPERS_HPP

#include "constants.hpp"
#include "ircconnector.hpp"

namespace Tsuki {
  // IRC functions

  //Join a channel
  void JoinChannel(const Channel& chan,Tsuki::IRCConnector& conn);
  void JoinChannel(const std::string& channel,Tsuki::IRCConnector& conn);

  //Send a normal message
  void SendMsg(const std::string& msg,Tsuki::IRCConnector& conn);
  void SendMsg(const char* command,const std::string& message,Tsuki::IRCConnector& conn);
  void SendMsg(const std::string& command,const std::string& msg,Tsuki::IRCConnector& conn);

  //Send NICK message
  void SendNick(std::string& bot_name,Tsuki::IRCConnector& conn);
  void SendNick(const std::string& nick,Tsuki::IRCConnector& conn);

  //Send USER message
  void SendUser(const User& user,const std::string& realname,
                const int& mode,Tsuki::IRCConnector& conn);
  void SendUser(const User& user,const char* realname,const int& mode,
                Tsuki::IRCConnector& conn);

  //Me message
  void SendMe(const std::string& message,const std::string& target,
              Tsuki::IRCConnector& conn);

  //PrivMsg message
  void SendPrivMsg(const std::string& target,const std::string& message,
                   Tsuki::IRCConnector& conn);

  //Send PONG message
  void SendPong(const std::string& contents,Tsuki::IRCConnector& conn);

  //Part message
  void SendPart(const std::string& channel,Tsuki::IRCConnector& conn);
  void SendPart(const std::string& channel,const std::string& message,
                Tsuki::IRCConnector& conn);
}
#endif
