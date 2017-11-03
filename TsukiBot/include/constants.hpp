#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#pragma once

#include <string>
#include <vector>
#include <algorithm>

namespace Tsuki {

  static constexpr char Space = static_cast<char>(' ');
  static constexpr char Null = static_cast<char>(0);  //Not to be confused with C define NULL
  static constexpr char Lf = static_cast<char>(10);  //Newline
  static constexpr char Cr = static_cast<char>(13);	 // Carriage Return
  static constexpr char LeftSlash = static_cast<char>(92);  //The character " \ "
  static constexpr char Dash  = static_cast<char>(45);    //The character " - "
  static constexpr char LeftSquareBrackets = static_cast<char>(91);  //The character  " [ "
  static constexpr char RightSquareBrackets = static_cast<char>(93);  //The character " ] "
  static constexpr char SingleQuote = static_cast<char>(96);	 //The character  " ' "
  static constexpr char Power = static_cast<char>(94);  //The character  "^"
  static constexpr char LeftCurlyBraces = static_cast<char>(123);  //The character  "{ "
  static constexpr char RightCurlyBraces = static_cast<char>(125);	 //The character  " } "
  
  enum class PacketType{
    RPL_LIST = 322,
    RPL_LISTEND = 323;
    RPL_ENDOFMOTD = 376,
    ERR_NOSUCHNICK = 401,
    ERR_NOSUCHSERVER = 402,
    ERR_NOSUCHCHANNEL = 403,
    ERR_CANNOTSENDTOCHAN = 404,
    ERR_TOOMANYCHANNELS = 405,
    ERR_WASNOSUCHNICK = 406,
    ERR_TOOMANYTARGETS = 407,
    ERR_NOORIGIN = 409,
    ERR_NORECIPIENT = 411,
    ERR_NOTEXTTOSEND = 412,
    ERR_NOTOPLEVEL = 413,
    PRIVMSG,
	JOIN,
	PART,
	KICK,
	INVITE,
	LIST,
	MODE,
	NICK,
    PING,
	PONG,
	QUIT,
	WHO,
    WHOIS,
	WHOWAS,
	NOTICE,
	OTHER
 };
 
  const std::string Join = "JOIN"; 

  enum ServerState
  {
    NOT_CONNECTED,
    SETTING_NICK,
    SETTING_USER,
    SETTING_PONG,
    WORKING
  };

  /* User class is used to store the username of a person or bot connected to the network.
   * Used in Prefix class and Join_Data struct.
   */
  class User {
  private:
    std::string _data;
    void Parse();

  public:
    User() : _data{} {}
    User(const std::string& data) : _data(data) { Parse(); }
    ~User() {}
    void operator= (const User& obj);
    void setData(const std::string& data);
    std::string getData() const{ return _data; }
  };

  /* Nick class stores the nickname of a connection to the network.
   * Used in Prefix class and Join_Data struct.
   */
  class Nick {
  private:
    std::string _data;
    void Parse();

  public:
    Nick() : _data{} {}
    Nick(const std::string& data) : _data(data) { Parse(); }
    ~Nick() {}
    void operator= (const Nick& obj);
    void setData(const std::string& data);
    std::string getData() const { return _data; }
  };

  class Channel {
  private:
    std::string _data;
    std::vector<Nick> chan_users;
    void Parse();

  public:
    Channel() : _data{} {}
    Channel(const std::string& data): _data(data), chan_users{} { Parse(); }
    ~Channel() {}
    void operator= (const Channel& obj);
    void setData(const std::string& data);
    void setUsers(const std::string& user_list);
    std::string getData() const{ return _data; }
    std::vector<Nick> getUserList() const{ return chan_users; }
  };

  class Prefix {
  private:
    std::string _hostname;
    Nick _nick;
    User _user;
    void Parse(const std::string& data);
  public:
    Prefix() : _hostname{}, _nick{}, _user{} {}
    Prefix(const std::string& data): _data(data) { Parse(); }
    ~Prefix() {}
    void operator= (const Prefix& obj);
    void setData(const std::string& data);
    void setNick(const std::string& nick);
    std::string getData() const { 
	  std::string temp = _nick.getData() + "!" + _user.getData() + "@" + _hostname;
	  return temp; 
	}
    std::string getNickData() const{ return _nick.getData(); }
    std::string getHostname() const{ return _hostname; }
    Nick getNick() const { return _nick; }
    User getUser() const{ return _user; }
  };

  /* This struct is used in joining to a given channel.
   * Used in IRCConnector class.
   */
  class Join_Data {
    private:
      std::string server;
      Channel chan;
      Nick nick;
      User user;
      std::string realname;
      std::string pass;
      unsigned int port;
    
    public:  
      Join_Data() : server{}, chan{}, nick{}, user{}, 
                    pass{}, port{6667} {}
      Join_Data(const std::string& serv,const std::string& channel,
                const std::string& nickname,const std::string& username,
                const std::string& rname,const std::string& password,
	            const unsigned int& p) : chan{channel}, 
	            nick{nickname}, user{username}, realname{rname} {
        server = serv;
        pass = password;  port =p;
      }
      ~Join_Data() {}
      void setUser(const std::string& obj) { user.setData(obj); }
      void setNick(const std::string& obj) { nick.setData(obj); }
      void setChan(const std::string& obj) { chan.setData(obj); }
      Nick getNick() const{ return nick; }
      Channel getChannel() const{ return chan; }
      User getUser() const{ return user; }
      std::string getRealName() const{ return realname; }
      std::string getPassword() const{ return pass; }
      unsigned int getPort() const{ return port; } 
  };
} //namespace Tsuki

#endif



