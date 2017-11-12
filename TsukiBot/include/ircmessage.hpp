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
 */

using namespace Tsuki;

namespace Tsuki {
  class IRCMessage {
  private:
    Prefix _prefix;  // Details of the sender
    std::string _command; // Privmsg or whois or ctcp
    std::string _content; // Data send by the sender
    std::string _sender; // Who send it(channel or user)
    PacketType _pckType;

    inline void setPrefix(const std::string& prefix) {
      _prefix.setData(prefix);
    }

    inline void setCommand(const std::string& command) {
      _command = command;
    }

    inline void setSender(const std::string& sender) {
      _sender = sender;
    }

    inline void setContent(const std::string& dataReceived) {
      _content = dataReceived;
    }

    inline void setPacketInfo(const PacketType& packet) {
      _pckType = packet;
    }

    inline void setPacketInfo(const unsigned short& packet) {
      _pckType = static_cast<PacketType>(packet);
    }

    inline std::string getContent() const { return _content; }

  public:
    IRCMessage() : _prefix{}, _command{}, _content{}, _sender{} {}
    IRCMessage(const std::string& message) {
      Parse(message);
    }
    IRCMessage(const IRCMessage& obj);
    IRCMessage(IRCMessage&& obj);
    void operator= (const IRCMessage& obj);
    ~IRCMessage() {}

    //Same functionality,but doesn't return anything
    void Parse(const std::string& data);

    inline std::string getPrefix() const { return _prefix.getData(); }
    inline std::string getCommand() const { return _command; }
    inline std::string getSender() const { return _sender; }
    inline PacketType getPacketInfo() const { return _pckType; }

    inline std::string getData() const {
      std::string temp = _prefix.getData() + " " + _command + " " +
                         _sender + " " + _content;
      return temp;
    }

    template<typename T>
    auto safe_iterate(T x,T y) {
      while(x!=y) {
         ++x;
       }
      return x;
    }
  };
} // namespace Tsuki

#endif


