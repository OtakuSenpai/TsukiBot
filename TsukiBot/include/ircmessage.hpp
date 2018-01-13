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

    void setPrefix(const std::string& prefix);
    void setCommand(const std::string& command);
    void setSender(const std::string& sender);
    void setContent(const std::string& dataReceived);
    void setPacketInfo(const PacketType& packet);
    void setPacketInfo(const unsigned short& packet);

  public:
    IRCMessage() : _prefix{}, _command{}, _content{}, _sender{} {}
    IRCMessage(const std::string& message) {
      Parse(message);
    }
    IRCMessage(const IRCMessage& obj);
    IRCMessage(IRCMessage&& obj);
    IRCMessage& operator= (const IRCMessage& obj);
    ~IRCMessage() {}

    std::string getPrefix() const;
    std::string getCommand() const;
    std::string getSender() const;
    std::string getContent() const;
    PacketType getPacketInfo() const;
    
    void clear();
    std::string getData() const;
    bool isServer() const;
    void Parse(const std::string& data);
  };
} // namespace Tsuki

#endif


