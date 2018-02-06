#include "ircmessage.hpp"
#include <regex>
#include <vector>
#include <iostream>

void Tsuki :: IRCMessage :: clear() {
  _command.clear();
  _sender.clear();
  _content.clear();
  _prefix.clear();
  _pckType = PacketType::NONE;
  _type = Type::none;
}

void Tsuki :: IRCMessage :: setPrefix(const std::string prefix,
                                      const Type& type,const bool msg_status) {
  _prefix.setData(prefix,type,msg_status);
}

void Tsuki :: IRCMessage :: setCommand(const std::string command) {
  _command = command;
}

void Tsuki :: IRCMessage :: setSender(const std::string sender) {
  _sender = sender;
}

void Tsuki :: IRCMessage :: setContent(const std::string dataReceived) {
  _content = dataReceived;
}

void Tsuki :: IRCMessage :: setPacketInfo(const PacketType packet) {
  _pckType = packet;
}

void Tsuki :: IRCMessage :: setPacketInfo(const unsigned short packet) {
  _pckType = static_cast<PacketType>(packet);
}

std::string Tsuki :: IRCMessage :: getData() const {
  std::string temp;

  if(_type == Type::ping) {
    temp = _command + " " + _content;
  }
  else if(_type == Type::join) {
    temp = _command + " " + _content;
  }
  else if(_type == Type::privmsg) {
    temp = _command + " " +  _sender + " " + _content;
  }
  else if(_type == Type::notice) {
    temp = _prefix.getData() + " " + _command + " " +
           _sender + " " + _content;
  }
  else if(_type == Type::mode) {
    temp = _prefix.getData() + " " + _command + " " +
           _sender + " " + _content;
  }
  else if(_type == Type::special) {
    temp = _prefix.getData() + " " + std::to_string(static_cast<int>(_pckType)) +
           " "  + _sender + " " + _content;
  }
  else if(_type == Type::normal) {
    temp = _prefix.getData() + " " + _command + " " +
                     _sender + " " + _content;
  }

  return temp;
}

std::string Tsuki ::IRCMessage :: getPrefix() const {
  return _prefix.getData();
}

std::string Tsuki ::IRCMessage :: getCommand() const {
  return _command;
}

std::string Tsuki :: IRCMessage :: getSender() const {
  return _sender;
}

std::string Tsuki :: IRCMessage :: getContent() const {
  return _content;
}

PacketType Tsuki :: IRCMessage :: getPacketInfo() const {
  return _pckType;
}

Type Tsuki :: IRCMessage :: getType() const {
  return _type;
}

bool Tsuki :: IRCMessage :: isServer() const {
  return _from_server;
}

Tsuki :: IRCMessage :: IRCMessage(const std::string& message) {
  handleParse(message);
}

void Tsuki :: IRCMessage :: handleParse(const std::string& message) {
  if(begins_with(message,"PING")) {
    _from_server = true;
    _type = Type::ping;
    _prefix.setStatus(_from_server,_type);
  }
  else if(begins_with(message,"JOIN")) {
    _from_server = true;
    _type = Type::join;
    _prefix.setStatus(_from_server,_type);
  }
  else if(begins_with(message,"PRIVMSG")) {
    _from_server = true;
    _type = Type::privmsg;
    _prefix.setStatus(_from_server,_type);
  }
  else if(parseNumeral(message,"NOTICE")) {
    _from_server = true;
    _type = Type::notice;
    _prefix.setStatus(_from_server,_type);
  }
  else if(parseNumeral(message,"MODE")) {
    _from_server = true;
    _type = Type::mode;
    _prefix.setStatus(_from_server,_type);
  }
  else if(parseNumeral(message,"353") || parseNumeral(message,"366") ||
          parseNumeral(message,"332") || parseNumeral(message,"331") ||
          parseNumeral(message,"333")) {
    _from_server = true;
    _type = Type::normal;
    _prefix.setStatus(_from_server,_type);
  }
  else if(parseNumeral(message,"001") || parseNumeral(message,"002") ||
          parseNumeral(message,"004") || parseNumeral(message,"005") ||
          parseNumeral(message,"252") || parseNumeral(message,"253") ||
          parseNumeral(message,"255") || parseNumeral(message,"250") ||
          parseNumeral(message,"266") || parseNumeral(message,"375") ||
          parseNumeral(message,"376") || parseNumeral(message,"372") ||
          parseNumeral(message,"265") || parseNumeral(message,"254") ||
          parseNumeral(message,"251") || parseNumeral(message,"003")) {
    _type = Type::special;
    _from_server = true;
    _prefix.setStatus(_from_server,_type);
  }
  else if(!begins_with(message,"PING") && !begins_with(message,"JOIN") &&
          !begins_with(message,"PRIVMSG") && !parseNumeral(message,"003") &&
          !parseNumeral(message,"NOTICE") && !parseNumeral(message,"MODE") &&
          !(parseNumeral(message,"001") || parseNumeral(message,"002") ||
           parseNumeral(message,"004") || parseNumeral(message,"005") ||
           parseNumeral(message,"252") || parseNumeral(message,"253") ||
           parseNumeral(message,"255") || parseNumeral(message,"250") ||
           parseNumeral(message,"266") || parseNumeral(message,"375") ||
           parseNumeral(message,"376") || parseNumeral(message,"372") ||
           parseNumeral(message,"265") || parseNumeral(message,"254") ||
           parseNumeral(message,"251") || parseNumeral(message,"003"))) {
    _from_server = false;
    _type = Type::normal;
    _prefix.setStatus(_from_server,_type);
  }
  else { _type = Type::other; }
  Parse(message);
}

Tsuki :: IRCMessage :: IRCMessage(const IRCMessage& obj) {
  _sender = obj.getSender();
  _content = obj.getContent();
  _command = obj.getCommand();
  _prefix = obj.getPrefix();
  _pckType = obj.getPacketInfo();
  _type = obj._type;
}

Tsuki :: IRCMessage :: IRCMessage(IRCMessage&& obj) {
  _sender = std::move(obj._sender);
  _content = std::move(obj._content);
  _command = std::move(obj._command);
  _prefix = std::move(obj._prefix);
  _pckType = std::move(obj._pckType);
  _type = std::move(obj._type);

}

IRCMessage& Tsuki :: IRCMessage :: operator= (const IRCMessage& obj) {
  _sender = obj._sender;
  _content = obj._content;
  _command = obj._command;
  _prefix = obj._prefix;
  _pckType = obj._pckType;
  _type = obj._type;
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

    // && (tempStr.substr(0,tempStr.find(" ")).find("net") !=
    // tempStr.substr(0,tempStr.find(" ")).size() - 3)
    if(tempStr.find_first_of(':',0) != std::string::npos && _type == Type::normal) {
      auto prefix = std::find(front,end,' ');
      auto tempPos1 = std::distance(front,prefix);
      setPrefix(tempStr.substr(0,tempPos1+1),Type::normal,false);
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
      }
      else if(regex_match(str2Cmp,integer)) { // if its integer
        setPacketInfo(std::stoi(str2Cmp));
      }

      tempStr = tempStr.substr(tempPos2+1);
      front = std::begin(tempStr);
      end = std::end(tempStr);

      // Get the sender
      auto sender = std::find(front,end,' ');
      tempPos2 = std::distance(front,sender);
      _sender = tempStr.substr(0,tempPos2);
      tempStr = tempStr.substr(tempPos2);

      front = std::begin(tempStr);
      end = std::end(tempStr);

      // Get the real data

      auto d = std::find(front,end,':');
      tempPos2 = std::distance(front,d);
      _content = tempStr.substr(tempPos2);
    }
    else if(_from_server && _type == Type::ping) {
      parsePing(tempStr);
    }
    else if(_from_server && _type == Type::join) {
      parseJoin(tempStr);
    }
    else if(_from_server && _type == Type::privmsg) {
      parsePrivmsg(tempStr);
    }
    else if(_from_server && _type == Type::notice) {
      parseNotice(tempStr);
    }
    else if(_from_server && _type == Type::mode) {
      parseMode(tempStr);
    }
    else if(_type == Type::special && _from_server) {
       parseSpecial(tempStr);
    }
    else if(_type == Type::normal && _from_server) {
      if(parseNumeral(tempStr,"353")) { parseNamelist(tempStr); }
      else if(parseNumeral(tempStr,"366")) { parseEndofNamelist(tempStr); }
      else if(parseNumeral(tempStr,"332")) { parseTopic(tempStr); }
      else if(parseNumeral(tempStr,"331")) { parseNoTopic(tempStr); }
      else if(parseNumeral(tempStr,"333")) { parseWhoTime(tempStr); }
    }
    else {
      std::string temp = "ircmessage.cpp : In Tsuki::IRCMessage::Parse(const std::string&) : \
                        Error while parsing data.The data is: \n" + data + "\n";
      throw  std::runtime_error(temp);
    }
  }
  catch(const std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
    clear();
  }
}

void Tsuki :: IRCMessage :: parsePing(std::string& tempStr) {
  _command = tempStr.substr(0,tempStr.find(" ",0));
  _content = tempStr.substr(tempStr.find(":"));
  _pckType = PacketType::OTHER;
}

void Tsuki ::IRCMessage :: parseJoin(std::string& tempStr) {
  _command = tempStr.substr(0,tempStr.find(" ",0));
  _content = tempStr.substr(tempStr.find(" "));
  _pckType = PacketType::OTHER;
}

void Tsuki :: IRCMessage :: parsePrivmsg(std::string& tempStr) {
  _command = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  _pckType = PacketType::OTHER;
  _content = tempStr.substr(tempStr.find(':'));
}

void Tsuki :: IRCMessage :: parseNotice(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::notice,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _command = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _content = tempStr.substr(tempStr.find(':'));
  _pckType = PacketType::OTHER;
}

void Tsuki :: IRCMessage :: parseMode(std::string& tempStr) {
  tempStr = tempStr.substr(1);
  _prefix.setNick(tempStr.substr(0,tempStr.find_first_of(" ",0)));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _command = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _content = tempStr.substr(tempStr.find(':'));
  _pckType = PacketType::OTHER;
}

void Tsuki :: IRCMessage :: parseSpecial(std::string& tempStr) {
  std::regex integer("[0-9]+"); // for numbers larger than 0..9
  std::regex alphabets("[A-Za-z]+"); //A~Z & a~z
  if(has_it(tempStr,"004") || has_it(tempStr,"005") ||
     has_it(tempStr,"252") || has_it(tempStr,"253") ||
     has_it(tempStr,"265") || has_it(tempStr,"266") ||
     has_it(tempStr,"254")) {
    setPrefix(tempStr.substr(0,tempStr.find_first_of(" ",0)),
              Type::special,_from_server);
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    std::string packet = tempStr.substr(0,tempStr.find_first_of(" ",0));
    if(regex_match(packet,integer)) { // if its integer
      setPacketInfo(std::stoi(packet));
    }
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    _sender = tempStr.substr(0,tempStr.find_first_of(" ",0));
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    _content = tempStr;
  }
  else if(has_it(tempStr,"001") || has_it(tempStr,"002") ||
          has_it(tempStr,"003") || has_it(tempStr,"251") ||
          has_it(tempStr,"255") || has_it(tempStr,"250") ||
          has_it(tempStr,"375") || has_it(tempStr,"372") ||
          has_it(tempStr,"376")) {
    setPrefix(tempStr.substr(0,tempStr.find_first_of(" ",0)),
              Type::special,_from_server);
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    std::string packet = tempStr.substr(0,tempStr.find_first_of(" ",0));
    if(regex_match(packet,integer)) { // if its integer
      setPacketInfo(std::stoi(packet));
    }
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    _sender = tempStr.substr(0,tempStr.find_first_of(" ",0));
    tempStr = tempStr.substr(tempStr.find(" ",0)+1);
    _content = tempStr;
  }
}

// :kornbluth.freenode.net 353 G33kb0i = #tsukibot :G33kb0i dx_ob
void Tsuki :: IRCMessage :: parseNamelist(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::normal,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  if(has_it(tempStr.substr(0,tempStr.find(" ",0)),"353")) {
    setPacketInfo(PacketType::RPL_NAMREPLY);
  }
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find("=",0)+1);
  _content = tempStr;
}

// :hobana.freenode.net 366 G33kb0i #tsukibot :End of /NAMES list.
void Tsuki :: IRCMessage :: parseEndofNamelist(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::normal,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  if(has_it(tempStr.substr(0,tempStr.find(" ",0)),"353")) {
    setPacketInfo(PacketType::RPL_ENDOFNAMES);
  }
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(":",0));
  _content = tempStr;
}

//:cherryh.freenode.net 332 G33kb0i ##llamas :The official #1 off-topic
void Tsuki :: IRCMessage :: parseTopic(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::normal,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  if(has_it(tempStr.substr(0,tempStr.find(" ",0)),"332")) {
    setPacketInfo(PacketType::RPL_TOPIC);
  }
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _content = tempStr;
}

//:cherryh.freenode.net 332 G33kb0i ##llamas :The official #1 off-topic
void Tsuki :: IRCMessage :: parseNoTopic(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::normal,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  if(has_it(tempStr.substr(0,tempStr.find(" ",0)),"331")) {
    setPacketInfo(PacketType::RPL_NOTOPIC);
  }
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _content = tempStr;
}

//:cherryh.freenode.net 333 G33kb0i ##llamas letty 1506827147
void Tsuki :: IRCMessage :: parseWhoTime(std::string& tempStr) {
  setPrefix(tempStr.substr(0,tempStr.find(" ",0)),Type::normal,_from_server);
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  if(has_it(tempStr.substr(0,tempStr.find(" ",0)),"333")) {
    setPacketInfo(PacketType::RPL_TOPICWHOTIME);
  }
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _sender = tempStr.substr(0,tempStr.find(" ",0));
  tempStr = tempStr.substr(tempStr.find(" ",0)+1);
  _content = tempStr;
}
