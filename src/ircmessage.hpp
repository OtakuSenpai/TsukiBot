#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

#include <iterator>
#include <stdexcept>
#include <algorithm>

#include "constants.hpp"

using namespace Tsuki;

namespace Tsuki {	
	
class IRCMessage
{
    private:
            std::string  _sender;
            Irc_Data msg_data;
       
    public:
	    
            IRCMessage() :  _sender{}, msg_data{} {}
	    
	    IRCMessage(const IRCMessage& obj);
	    
	    void operator= (const IRCMessage& obj)
	    {
		    _sender = obj.RetSender();
		    msg_data = obj.RetMsgData();
	    }
	    
	    ~IRCMessage() {}
	    
	    
	    /* Parses a reply or a data given to the bot and
	     * returns an object which can be used to better know the message.
	     */ 
	    Irc_Data RParse(std::string& data);
	    
	    //Same functionality,but doesn't return anything 
	    void Parse(std::string& data);
           
	    //Return Sender
	    std::string RetSender() const { return _sender; }
	    
	    //Return Irc_Data
	    Irc_Data RetMsgData() const { return msg_data; }
	    
	    template<typename T> 
	    auto safe_iterate(T x,T y) 
	   { 
		    while(x!=y)
		    {
			 ++x;
		    }
		    return x;
	   }
};
	    
}	    

#endif


