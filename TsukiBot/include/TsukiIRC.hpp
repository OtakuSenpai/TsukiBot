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

#ifndef TSUKIIRC_HPP
#define TSUKIIRC_HPP

#include <vector>
#include <string>
#include <iterator>
#include <chrono>
#include <map>

#include "irchelpers.hpp"
#include "kernel.hpp"


using namespace std::chrono;
using namespace Tsuki;
using namespace Tryx;

namespace Tsuki
{
  class Bot {
  protected:
    bool running, disconnect;
    bool connected = false,joined = false;
    std::chrono::seconds wait_time{5};
    IRCConnector conn;
    Join_Data server_data;
    std::vector<Channel> chan_list;
    std::vector<Tsuki::IRCMessage> msglogs;
    std::string bot_name,second_name;
    ServerState state;
    Kernel kernel;
    std::string specialChar;
    std::string plgPath;
    std::map<std::string,std::vector<std::string>> pluginSubStrs;

    //Utility functions
    std::vector<Tsuki::Nick> get_user_list(const std::string& from);
    std::string get_text_after_command(const std::string& message,const char* command);
    bool has_in_chan(const std::string& name,const std::string& channel);
    void handle_msg(std::string& msg);
    void segragrator(const std::string& message,const char* data,
                     std::vector<Tsuki::IRCMessage>& msg);
    void makeSpace(std::vector<IRCMessage> msgs);

    inline void setState(const ServerState& s) { state = s; }
    inline void setRunning(const bool& run) { running = run; }
    void setName(const std::string& name);
    inline bool isConnected() { return connected; }
    inline void setConnected(const bool& connect) { connected = connect; }

    //Set the connection
    void SetConn();
    //Set the channel user list
    void handleNickList(IRCMessage& temp);
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
       const std::string& password,const unsigned int& port,
       const std::string& special,const std::string& path) : conn{server,port},
       server_data{server,channel,nick,user,realname,password,port},
       msglogs{}, bot_name{nick}, second_name{nick2}, specialChar(special),
       plgPath(path) {
         setName(nick);
         LoadPlugins(plgPath);
    }
    ~Bot() { UnloadPlugins(); }

    inline std::string getName() const{ return bot_name; }
    inline ServerState getState() const{ return state; }
    inline bool isRunning() const{ return running; }

    //Connect to the server
    void Connect();

    //Disconnect
    void Disconnect();

    //Get list of plugin's size
    inline int getKernelSize() const{ return kernel.getSize(); }
  };
} // namespcace Tsuki

#endif
