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

#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

#include <iterator>
#include <stdexcept>
#include <algorithm>

#include "constants.hpp"

/* Example IRC messages
 * :Nawab!~OtakuSenp@unaffiliated/otakusenpai PRIVMSG #freenode :like this one
 * :hobana.freenode.net 311 Scott` Nawab ~OtakuSenp unaffiliated/otakusenpai * :OtakuSenpai
 * The above is a whois message, with ":hoba...e.net" being the prefix,
 * just have hobana.freenode.net assigned to the _prefix->hostname.
 * Basically: Ignore spaces, take single word parameter if it does not start with
   ':', take rest of the line if it does start with ':'. Exception: The first
   parameter never starts with ':', even if it does.
 */

using namespace Tsuki;

namespace Tsuki {
  class IRCMessage {
  private:
    Prefix _prefix;  // Details of the sender
    std::string _command; // Privmsg or whois or ctcp
    std::string _content; // Data send by the sender
    std::string _sender; // Who send it(channel or user)
    PacketType _pckType; // Type of packet
    Type _type;
    bool _from_server = true; // If true, it is from server
                            // If false, it is from client

    friend class Bot;

    void setPrefix(const std::string prefix,const Type& type,const bool msg_status);
    void setCommand(const std::string command);
    void setSender(const std::string sender);
    void setContent(const std::string dataReceived);
    void setPacketInfo(const PacketType packet);
    void setPacketInfo(const unsigned short packet);
    void Parse(const std::string& data);

    void parsePing(std::string& msg);
    void parseJoin(std::string& msg);
    void parsePrivmsg(std::string& msg);
    void parseNotice(std::string& msg);
    void parseMode(std::string& msg);
    void parseSpecial(std::string& msg);
    void parseNamelist(std::string& msg);
    void parseEndofNamelist(std::string& msg);
    void parseTopic(std::string& msg);
    void parseNoTopic(std::string& msg);
    void parseWhoTime(std::string& msg);

  public:
    IRCMessage() : _prefix{}, _command{}, _content{}, _sender{} {}
    IRCMessage(const std::string& message);
    IRCMessage(const IRCMessage& obj);
    IRCMessage(IRCMessage&& obj);
    IRCMessage& operator= (const IRCMessage& obj);
    ~IRCMessage() {}

    std::string getPrefix() const;
    std::string getCommand() const;
    std::string getSender() const;
    std::string getContent() const;
    PacketType getPacketInfo() const;
    Type getType() const;

    void clear();
    std::string getData() const;
    bool isServer() const;
    void handleParse(const std::string& msg);
  };
} // namespace Tsuki

#endif
