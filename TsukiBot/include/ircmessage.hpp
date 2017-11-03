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
    std::string _data; // Data send by the sender
    std::string _sender; // Who send it(channel or user)
    PacketType pckType;
    
    void setPrefix(const std::string& pref) { prefix.setData(pref); }
    void setCommand(const std::string& obj) { command = obj; }
    std::string getSndData() const { return _data; }
    
  public:
    IRCMessage() :  _sender{}, msg_data{} {}

	IRCMessage(const IRCMessage& obj);
	 
	void operator= (const IRCMessage& obj) const {
	  _sender = std::move(obj.getSender());
      _data = std::move(obj.get
      msg_data = std::move(obj.getMsgData();
    }
    ~IRCMessage() {}

    //Same functionality,but doesn't return anything
	void Parse(std::string& data);

    std::string getPrefix() const { return prefix.getData(); }
    std::string getCommand() const { return command; }
    
    std::string getData() const {
	  std::string temp = _prefix.getData() + " " + command + " " +
	                     _sender + " " + _data;
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


