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


#ifndef IRCCONNECTOR_HPP
#define IRCCONNECTOR_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"

#include "ircmessage.hpp"

using namespace Tsuki;

namespace Tsuki
{
  class IRCConnector {
  private:
    IPaddress ipaddress;
    TCPsocket tcpsock;
    char* buffer = nullptr;
    const int buf_size =512;
    bool connected = false;

  public:
    IRCConnector(const std::string& server,const unsigned int& port);
    ~IRCConnector();

    inline TCPsocket RetTCPsocket() { return tcpsock; }
    inline bool isConnected() { return connected; }
    inline char* RetBuffer() { return buffer; }

    //Connect to a server by using the Join_Data variable
    void Connect();

    //Disconnect from the server
    void DisConnect() { SDLNet_TCP_Close(tcpsock); }

    //Send Data to the server
    void SendData(const char* data);
    void SendData(const std::string& data);
    void SendData(const IRCMessage& data);

    //Receive data from the server
    std::string RecvData();
    bool RecvData(std::string& message);
    bool RecvData(Tsuki::IRCMessage& message);
  };
} // namespace Tsuki

#endif
