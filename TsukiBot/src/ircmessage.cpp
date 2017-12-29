#include "ircmessage.hpp"
#include <regex>
#include <vector>
#include <iostream>

std::string Tsuki :: IRCMessage :: getData() const {
  std::string temp = _prefix.getData() + " " + _command + " " +
                     _sender + " " + _content;
  return temp;
}

Tsuki :: IRCMessage :: IRCMessage(const IRCMessage& obj) {
  _sender = obj.getSender();
  _content = obj.getContent();
  _command = obj.getCommand();
  _prefix = obj.getPrefix();
}

Tsuki :: IRCMessage :: IRCMessage(IRCMessage&& obj) {
  _sender = std::move(obj._sender);
  _content = std::move(obj._content);
  _command = std::move(obj._command);
  _prefix = obj._prefix;
}

IRCMessage& Tsuki :: IRCMessage :: operator= (const IRCMessage& obj) {
  _sender = obj._sender;
  _content = obj._content;
  _command = obj._command;
  _prefix = obj._prefix;
  return *this;
}

/* Example IRC messages
 * :Nawab!~OtakuSenp@unaffiliated/otakusenpai PRIVMSG #freenode :like this one
 * :OtakuSenpai!~OtakuSenp@unaffiliated/otakusenpai PRIVMSG ##llamas :,moo
 * :hobana.freenode.net 311 Scott` Nawab ~OtakuSenp unaffiliated/otakusenpai * :OtakuSenpai
 * :slow-iguana!~d@gateway/vpn/privateinternetaccess/d PRIVMSG ##llamas :good to see
 */

void Tsuki :: IRCMessage :: Parse(const std::string& data) {
  try {
    std::string tempStr = data;
    auto front = std::begin(tempStr);
    auto end = std::end(tempStr);
    std::regex integer("[0-9]+"); // for numbers larger than 0..9
    std::regex alphabets("[A-Za-z]+"); //A~Z & a~z

    if(tempStr.find_first_of(':',0) != std::string::npos) {
      // Get the prefix
      front += tempStr.find_first_of(':',0);
      auto prefix = std::find(front,end,' ');
      auto tempPos1 = std::distance(front,prefix);
      _prefix.setData(data.substr(0,tempPos1+1));
      tempStr = tempStr.substr(tempPos1+1);
      front = std::begin(tempStr);
      end = std::end(tempStr);

      // Get the command
      auto command = std::find(front,end,' ');
      auto tempPos2 = std::distance(front,command);
      std::string str2Cmp = tempStr.substr(0,tempPos2);
      if(regex_match(str2Cmp,alphabets)) {
        _command = str2Cmp;
        setPacketInfo(999);
        std::cout<<"Alpha: "<<_command<<std::endl;
      }
      else if(regex_match(str2Cmp,integer)) { // if its integer
        setPacketInfo(std::stoi(str2Cmp));
        std::cout<<"Numeric: "<<static_cast<int>(getPacketInfo())<<std::endl;
      }

      tempStr = tempStr.substr(tempPos2+1);
      front = std::begin(tempStr);
      end = std::end(tempStr);

      // Get the sender
      auto sender = std::find(front,end,' ');
      tempPos2 = std::distance(front,sender);
      _sender = tempStr.substr(0,tempPos2);
      tempStr = tempStr.substr(tempPos2);
      front = safe_iterate(front,sender);

      front = std::begin(tempStr);
      end = std::end(tempStr);

      // Get the real data
      auto d = std::find(front,end,':');
      tempPos2 = std::distance(front,d);
      _content = tempStr.substr(tempPos2);
    }
    else {
      std::string temp("ircmessage.cpp : In Tsuki::IRCMessage::\
                    Parse(const std::string&) : Error while parsing data.\n");
      throw  std::runtime_error(temp);
    }
  }
  catch(const std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

