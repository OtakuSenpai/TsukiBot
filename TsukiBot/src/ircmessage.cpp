#include "ircmessage.hpp"
#include <regex>
#include <iostream>

Tsuki :: IRCMessage :: IRCMessage(const IRCMessage& obj) {
  _sender = obj.getSender();
  _data = obj.getSndData();
  _command = obj.getCommand();
  _prefix = obj.getPrefix();
}

Tsuki :: IRCMessage :: IRCMessage(IRCMessage&& obj) {
  _sender = std::move(obj._sender);
  _data = std::move(obj._content);
  _command = std::move(obj._command);
  _prefix = obj._prefix;
}

void Tsuki :: IRCMessage :: operator= (const IRCMessage& obj) {
  _sender = std::move(obj._sender);
  _data = std::move(obj._content);
  _command = std::move(obj._command);
  _prefix = obj._prefix;
}

/* Example IRC messages
 * :Nawab!~OtakuSenp@unaffiliated/otakusenpai PRIVMSG #freenode :like this one
 *
 * :hobana.freenode.net 311 Scott` Nawab ~OtakuSenp unaffiliated/otakusenpai * :OtakuSenpai
 */

void Tsuki :: IRCMessage :: Parse(std::string& data) {
  try {
    auto front = std::begin(data);
    auto end = std::end(data);
    std::regex integer("[[:d:]]+");

    if(*front == ':') {
      // Get the prefix
      auto prefix = std::find(++front,end,' ');
      _prefix.setData(data.assign(front,prefix));
      auto tempPos1 = std::distance(front,prefix);
      data = data.substr(tempPos1);
      front = safe_iterate(front,prefix);

      // Get the command
      auto command = std::find(front,end,' ');
      std::string tempStr = data.assign(front,command);
      if(regex_match(tempStr,integer)) // if its integer
        setPacketInfo(std::stoi(tempStr));
      else if(tempStr == "INVITE" || tempStr == "TOPIC" ||
        tempStr == "JOIN" || tempStr == "KICK" || tempStr == "PART" ||
        tempStr == "NOTICE" || tempStr == "LIST" ||
        tempStr == "MODE"  || tempStr == "PING" || tempStr == "PONG" ||
        tempStr == "QUIT" || tempStr == "WHO" || tempStr == "WHOIS" ||
        tempStr == "WHOWAS" || tempStr == "PRIVMSG" ) {
        if(tempStr == "INVITE") setPacketInfo(111);
        else if(tempStr == "TOPIC") setPacketInfo(111);
        else if(tempStr == "JOIN") setPacketInfo(111);
        else if(tempStr == "KICK") setPacketInfo(111);
        else if(tempStr == "PART") setPacketInfo(111);
        else if(tempStr == "PRIVMSG") setPacketInfo(111);
        else if(tempStr == "NOTICE") setPacketInfo(111);
        else if(tempStr == "LIST") setPacketInfo(111);
        else if(tempStr == "MODE") setPacketInfo(111);
        else if(tempStr == "PING") setPacketInfo(111);
        else if(tempStr == "PONG") setPacketInfo(111);
        else if(tempStr == "QUIT") setPacketInfo(111);
        else if(tempStr == "WHO") setPacketInfo(111);
        else if(tempStr == "WHOIS") setPacketInfo(111);
        else if(tempStr == "WHOWAS")  setPacketInfo(111);
      }

      auto tempPos2 = std::distance(front,command);
      data = data.substr(tempPos2);
      front = safe_iterate(front,command);

      // Get the sender
      auto sender = std::find(front,end,' ');
      _sender = data.assign(front,sender);
      tempPos2 = std::distance(front,sender);
      data = data.substr(tempPos2);
      front = safe_iterate(front,sender);

      // Get the real data
      auto d = std::find(front,end,':');
      _content = data.assign(++d,end);
      data.clear();
    }
    else {
      std::string temp("ircmessage.cpp : In Tsuki::IRCMessage::\
                    Parse(std::string&) : Error while parsing data.\n");
      throw  std::runtime_error(temp);
    }
  }
  catch(const std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

