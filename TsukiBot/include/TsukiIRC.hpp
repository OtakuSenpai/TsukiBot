#ifndef TSUKIIRC_HPP
#define TSUKIIRC_HPP

#include <vector>
#include <string>
#include <iterator>
#include <chrono>

#include "ircconnector.hpp"
#include "kernel.hpp"


using namespace std::chrono;
using namespace Tsuki;
using namespace Tryx;

namespace Tsuki
{
  class Bot {
  protected:
    bool running;
    bool connected = false,joined = false;
    std::chrono::seconds wait_time{5};
    IRCConnector conn;
    Join_Data server_data;
    std::vector<Channel> chan_list;
    std::vector<std::string> msglogs;
    std::string bot_name,second_name;
    ServerState state;
    Kernel kernel;
    std::string plgPath;

    //Utility functions
    bool begins_with(const std::string& message,const char* command);
    bool has_alnum(const std::string& data);
    bool has_only_spec(const std::string& data);
    bool has_only_space(const std::string& data);
    bool has_it(const std::string& data,const char* command);
    bool has_it(const std::string& data,const char& command);
    std::vector<Tsuki::Nick> get_user_list(const std::string& from);
    std::string get_text_after_command(const std::string& message,const char* command);
    bool has_in_chan(const std::string& name,const std::string& channel);
    void handle_msg(std::string& msg);
    void segragrator(const std::string& message,const char* data);

    inline void setState(const ServerState& s) { state = s; }
    inline void setRunning(const bool& run) { running = run; }
    void setName(const std::string& name);
    inline bool isConnected() { return connected; }
    inline void setConnected(const bool& connect) { connected = connect; }

    //Set the connection
    void SetConn();

    //Plugins part
    //Load a plugin or plugins
    void LoadPlugin(const std::string& path);
    void LoadPlugins(const std::string& path);

    //Unload plugins
    void UnloadPlugins(){ kernel.unloadPlugins(); }

  public:
    Bot(const std::string& server,const std::string& channel,
      const std::string& nick,const std::string& nick2,
      const std::string& user,const std::string& realname,
      const std::string& password,
      const unsigned int& port) : conn{server,port},
      server_data{server,channel,nick,user,realname,password,port},
      msglogs{}, bot_name{nick}, second_name{nick2}
      {
        setName(nick);
        std::string mooplg{"./plugins/libmooplg.so"};
        std::string pingplg{"./plugins/libpingplg.so"};
        LoadPlugin(pingplg);
        LoadPlugin(mooplg);
      }
    ~Bot() { UnloadPlugins(); }

    inline std::string getName() const{ return bot_name; }
    inline ServerState getState() const{ return state; }
    inline bool isRunning() const{ return running; }

    //Connect to the server
    void Connect();

    //Disconnect
    void Disconnect();

    //Join a channel
    void JoinChannel(const Channel& chan);
    void JoinChannel(const std::string& channel);

    //Send a normal message
    void SendMsg(const std::string& msg);
    void SendMsg(const char* command,const std::string& message);
    void SendMsg(const std::string& command,const std::string& msg);

    //Send NICK message
    void SendNick();
    void SendNick(const std::string& nick);

    //Send USER message
    void SendUser(const User& user,const std::string& realname,
                  const int& mode);
    void SendUser(const User& user,const char* realname,const int& mode);

    //Me message
    void SendMe(const std::string& message,const std::string& target);

    //PrivMsg message
    void SendPrivMsg(const std::string& target,const std::string& message);

    //Send PONG message
    void SendPong(const std::string& contents);

    //Part message
    void SendPart(const std::string& channel);
    void SendPart(const std::string& channel,const std::string& message);

    //Add a channel
    void AddChannel(const std::string& channel,const std::string& command);

    //Get list of plugin's size
    inline int getSize() const{ return kernel.getSize(); }
  };
} // namespcace Tsuki

#endif
