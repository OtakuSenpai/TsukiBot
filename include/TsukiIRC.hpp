#ifndef  TSUKIIRC_HPP
#define TSUKIIRC_HPP

#include <vector>
#include <string>
#include <iterator>

#include "ircconnector.hpp"

using namespace Tsuki;

namespace Tsuki
{
  class Bot {
  protected:
    bool running;
    IRCConnector conn;
    Join_Data server_data;
    std::vector<Channel> chan_list;
    std::vector<std::string> msglogs;
    std::string BotName;
    ServerState state;

    bool begins_with(std::string message,const char* command);
    bool has_alnum(std::string data);
    bool has_only_spec(std::string data);
    bool has_only_space(std::string data);
    bool has_it(std::string data,const char* command);
    bool has_it(std::string data,char command);
    std::vector<Tsuki::Nick> get_user_list(std::string& from);
    std::string get_text_after_command(std::string message,const char* command);
    bool has_in_chan(std::string name,std::string& channel);
    virtual void handle_msg(std::string& msg);
    void GetState(ServerState s) { state = s; }

  public:
    Bot(std::string& server,unsigned int port=6667) : conn{server,port}, msglogs{}, BotName{} {}
    Bot(std::string& server,std::string& channel,
	std::string& nick,std::string& user,
	std::string& password,
	unsigned int& port) : conn{server,port}, server_data{server,channel,nick,user,password,port},
			      msglogs{},BotName{nick} { setName(nick); }
    virtual ~Bot() {}
    void segragrator(std::string& message,const char* data);
    void setName(std::string& name);
    std::string getName() const{ return BotName; }
    ServerState getState() { return state; }
    bool isRunning() const{ return running; }

    //Connect to the server
    virtual void Connect();

    //Disconnect
    void Disconnect();

    //Join a channel
    void JoinChannel(Channel& chan);
    void JoinChannel(std::string& channel);

    //Send a normal message
    void SendMsg(std::string& msg);
    void SendMsg(const char* command,std::string& message);

    //Send NICK message
    void SendNick();
    void SendNick(std::string& nick);

    //Send USER message
    void SendUser(User user,std::string& realname,int mode);
    void SendUser(User user,const char* realname,int mode);

    //Me message
    void SendMe(std::string& message,std::string& target);

    //Send PONG message
    void SendPong(std::string& contents);

    //Add a channel
    void AddChannel(std::string& channel,std::string& command);
  };
} // namespcace Tsuki

#endif
