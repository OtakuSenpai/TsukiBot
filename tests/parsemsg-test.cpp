#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include "ircmessage.hpp"

std::vector<IRCMessage> msglogs;
std::string specialChar = ",";

void makeSpace(std::vector<IRCMessage> msgs) {
  std::move(msgs.begin() + 3000, msgs.end(),msgs.begin());
  msgs.resize(2000);
}


void segragrator(const std::string& message,const char* data, 
                 std::vector<Tsuki::IRCMessage>& msg) {
  size_t pos = 0;
  std::string token,delimiter(data),tempValue = message;

  while ((pos = tempValue.find(delimiter)) != std::string::npos) {
    token = tempValue.substr(0, pos);
    Tsuki::IRCMessage temp(token);
    msg.push_back(temp); temp.clear(); token.clear();
    tempValue.erase(0, pos + delimiter.length());
  }
}

void handle_msg(std::string& message) {
  try {
    std::cout<<std::endl<<"Server Data: "<<message<<std::endl<<std::endl;
    std::vector<IRCMessage> tempMsgs; segragrator(message, "\r\n",tempMsgs); // separate whole messages
    std::cout<<"Messages received: "<<msglogs.size()<<std::endl;
    for(auto&& i: tempMsgs) {
      if(i.getType() != Type::special && i.getType() != Type::join &&
         i.getType() != Type::ping && i.getType() != Type::notice) {
        std::cout<<"Content: "<<i.getContent()<<std::endl;
        std::string tempContent = i.getContent().substr(1);
        if(has_it(tempContent,std::string(specialChar + "join"))) {
          std::string temp = i.getContent().substr(i.getContent().find(" "));
          std::cout<<"Channel is: "<<temp<<std::endl;
          //JoinChannel(temp);
          //chan_list.push_back(Tsuki::Channel(temp));
        }
        else if(has_it(tempContent,std::string(specialChar + "part"))) {
          // $part ##llamas
          // $part ##llamas bye
          //Content: :$part ##llamas

          std::string total,chan,message,Cmd;
          size_t pos1 = -1;

          Cmd = specialChar + "part";
          total = tempContent.substr(total.find(' '));
          if(std::isspace(total.at(0))) {
            total = total.substr(1);
          }
          std::cout<<"Total: "<<total<<std::endl;
          auto pos = total.find(' ');
          if(pos != std::string::npos) {
            chan = total.substr(0,pos);
            message = total.substr(pos+1);
          }
          else { chan = total; }
        } 
        else if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_NAMREPLY))) ||
                has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_TOPIC)))) {
          if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_NAMREPLY)))) {
            //:cherryh.freenode.net 353 G33kb0i = #tsukibot :G33kb0i OtakuSenpai
            std::string tempChan = i.getContent().substr(0,i.getContent().find(" "));
            std::string nameList = i.getContent().substr(i.getContent().find(":"));

            //for(auto j: chan_list) {
              //if(j.getData() == tempChan) {
                //j.setUsers(nameList); break;
              //}
            //}
          }
          else if(has_it(tempContent,std::to_string(static_cast<int>(PacketType::RPL_TOPIC)))) {
            //:cherryh.freenode.net 332 G33kb0i ##llamas :The official #1 off-topic

            std::string chan = i.getContent().substr(0,i.getContent().find(" "));
            std::string topic = i.getContent().substr(i.getContent().find(":"));
            //for(auto j: chan_list) {
              //if(j.getData() == chan) { j.setTopic(topic); break; }
            //}
          }
        }
        else if(has_it(tempContent,std::string(specialChar + "quit"))) {
         // Disconnect(); disconnect = true; break;
        }
      }
    }

    msglogs.resize(tempMsgs.size() + msglogs.size());
    std::move_backward(tempMsgs.begin(), tempMsgs.end(), msglogs.end());

    if(msglogs.size() > 5000) { makeSpace(msglogs); }
    message.clear();
  }
  catch(std::exception& e){
    std::cout<<"Caught exception: \n"<<e.what()<<std::endl
             <<"Data is: "<<message<<std::endl;
  }
}

using namespace Tsuki;

int main() {
  std::string temp;
  std::ifstream fio;
  fio.open("irclog.txt", std::ios::in);
  if(fio.bad() || fio.fail()) {
    std::cout<<"Bad file operation!";
    exit(0);
  }
  while(std::getline(fio,temp,'\n')) {
    handle_msg(temp);
  }
  fio.close();
  return 0;
}
