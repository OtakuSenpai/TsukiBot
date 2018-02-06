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
