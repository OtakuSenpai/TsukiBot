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
  static constexpr char Cr = static_cast<char>(13);  // Carriage Return
  static constexpr char LeftSlash = static_cast<char>(92);  //The character " \ "
  static constexpr char Dash  = static_cast<char>(45);    //The character " - "
  static constexpr char LeftSquareBrackets = static_cast<char>(91);  //The character  " [ "
  static constexpr char RightSquareBrackets = static_cast<char>(93);  //The character " ] "
  static constexpr char SingleQuote = static_cast<char>(96);     //The character  " ' "
  static constexpr char Power = static_cast<char>(94);  //The character  "^"
  static constexpr char LeftCurlyBraces = static_cast<char>(123);  //The character  "{ "
  static constexpr char RightCurlyBraces = static_cast<char>(125);   //The character  " } "

  enum class PacketType{
    RPL_WELCOME = 1,    // First four mean successful connection
    RPL_YOURHOST = 2,
    RPL_CREATED = 3,
    RPL_MYINFO = 4,
    RPL_BOUNCE = 5,   // Sent by the server to a user to suggest an alternative
                      // server. This is often used when the connection is
                      // refused because the server is already full.
    RPL_AWAY = 301,           // "<nick> :<away message>"
    RPL_UNAWAY = 305,         // ":You are no longer marked as being away"
    RPL_NOWAWAY = 306,        // ":You have been marked as being away"
    RPL_WHOISUSER = 311,      // "<nick> <user> <host> * :<real name>"
    RPL_WHOISSERVER = 312,    // "<nick> <server> :<server info>"
    RPL_WHOISOPERATOR = 313,  // "<nick> :is an IRC operator"
    RPL_WHOISCHANNELS = 319,  // "<nick> :*( ( "@" / "+" ) <channel> " " )"
    RPL_ENDOFWHOIS = 318,     // "<nick> :End of WHOIS list"
    RPL_WHOWASUSER = 314,     // "<nick> <user> <host> * :<real name>"
    RPL_ENDOFWHOWAS = 369,    // "<nick> :End of WHOWAS"
    RPL_LIST = 322,           // "<channel> <# visible> :<topic>"
    RPL_LISTEND = 323,        // ":End of LIST"
    RPL_NOTOPIC = 331,        // "<channel> :No topic is set"
    RPL_TOPIC = 332,          // "<channel> :<topic>"
    RPL_INVITING = 341,       // "<channel> <nick>"
    RPL_WHOREPLY = 352,       // "<channel> <user> <host> <server> <nick>
                              // ("H" / "G" > ["*"] [ ( "@" / "+" ) ]
                              // :<hopcount> <real name>"
    RPL_ENDOFWHO = 315,       // "<name> :End of WHO list"
    RPL_BANLIST = 367,        // "<channel> <banmask>"
    RPL_ENDOFBANLIST = 368,   // "<channel> :End of channel ban list"
    RPL_INFO = 371,           // ":<string>"
    RPL_ENDOFINFO = 374,      // ":End of INFO list"
    RPL_MOTDSTART = 375,      // ":- <server> Message of the day - "
    RPL_ENDOFMOTD = 376,      // ":End of MOTD command"
    RPL_MOTD = 372,           // ":- <text>"
    RPL_YOUREOPER = 381,      // ":You are now an IRC operator", send by
                              // an OPER message
    RPL_TIME = 391,           // "<server> :<string showing server's
                              // local time>"
    RPL_UMODEIS = 221,        // "<user mode string>"
    RPL_LUSERCLIENT = 251,    // ":There are <integer> users and <integer>
                              // services on <integer> servers"
    RPL_LUSEROP = 252,        // "<integer> :operator(s) online"
    RPL_LUSERUNKNOWN = 253,   // "<integer> :unknown connection(s)"
    RPL_LUSERCHANNELS = 254,  // "<integer> :channels formed"
    RPL_LUSERME = 255,        // ":I have <integer> clients and <integer>
                              // servers"

    ERR_NOSUCHNICK = 401,       // "<nickname> :No such nick/channel"
    ERR_NOSUCHSERVER = 402,     // "<server name> :No such server"
    ERR_NOSUCHCHANNEL = 403,    // "<channel name> :No such channel"
    ERR_CANNOTSENDTOCHAN = 404, // "<channel name> :Cannot send to channel"
    ERR_TOOMANYCHANNELS = 405,  // "<channel name> :You have joined too many channels"
    ERR_WASNOSUCHNICK = 406,    // "<nickname> :There was no such nickname"
    ERR_TOOMANYTARGETS = 407,   // "<target> :<error code> recipients. <abort message>"
    ERR_NOORIGIN = 409,         // ":No origin specified"
                                // PING or PONG message missing the originator parameter.
    ERR_NORECIPIENT = 411,      // ":No recipient given (<command>)"
    ERR_NOTEXTTOSEND = 412,     // ":No text to send"
    ERR_NOTOPLEVEL = 413,       // "<mask> :No toplevel domain specified"
    ERR_BADMASK = 415,          // "<mask> :Bad Server/host mask"
    ERR_UNKNOWNCOMMAND = 421,   // "<command> :Unknown command"
    ERR_NOMOTD = 422,           //  ":MOTD File is missing"
    ERR_NOADMININFO = 423,      // "<server> :No administrative info available"
    ERR_FILEERROR = 424,        // ":File error doing <file op> on <file>"
                                // Generic error message used to report a failed file
                                // operation during the processing of a message.
    ERR_NONICKNAMEGIVEN = 431,  // ":No nickname given"
    ERR_ERRONEUSNICKNAME = 432, // "<nick> :Erroneous nickname"
                                // Returned after receiving a NICK message which contains
                                // characters which do not fall in the defined set.
    ERR_NICKNAMEINUSE = 433,    // "<nick> :Nickname is already in use"
    ERR_NICKCOLLISION = 436,    // "<nick> :Nickname collision KILL from <user>@<host>"
                                // Returned by a server to a client when it detects a
                                // nickname collision (registered of a NICK that
                                // already exists by another server)
    ERR_UNAVAILRESOURCE = 437,  // "<nick/channel> :Nick/channel is temporarily unavailable"
                                // Returned by a server to a user trying to join a channel
                                // currently blocked by the channel delay mechanism.
                                // Returned by a server to a user trying to change nickname
                                // when the desired nickname is blocked by the nick delay
                                // mechanism.
    ERR_USERNOTINCHANNEL = 441, // "<nick> <channel> :They aren't on that channel"
    ERR_NOTONCHANNEL = 442,     // "<channel> :You're not on that channel"
    ERR_USERONCHANNEL = 443,    // "<user> <channel> :is already on channel"
    ERR_NOLOGIN = 444,          // "<user> :User not logged in"
    ERR_NOTREGISTERED = 451,    // ":You have not registered"
                                // Returned by the server to indicate that the client
                                // MUST be registered before the server will allow it
                                // to be parsed in detail.
    ERR_NEEDMOREPARAMS = 461,   // "<command> :Not enough parameters"
                                // Returned by the server by numerous commands to
                                // indicate to the client that it didn't supply enough
                                // parameters.
    ERR_ALREADYREGISTRED = 462, // ":Unauthorized command (already registered)"
                                // Returned by the server to any link which tries to
                                // change part of the registered details (such as
                                // password or user details from second USER message).
    ERR_NOPERMFORHOST = 463,    // ":Your host isn't among the privileged"
                                // Returned to a client which attempts to register with
                                // a server which does not been setup to allow
                                // connections from the host the attempted connection
                                // is tried.
    ERR_PASSWDMISMATCH = 464,   // ":Password incorrect"
                                // Returned to indicate a failed attempt at registering
                                // a connection for which a password was required and
                                // was either not given or incorrect.
    ERR_YOUREBANNEDCREEP = 465, // ":You are banned from this server"
    ERR_YOUWILLBEBANNED = 466,  // Sent by a server to a user to inform that access to the
                                // server will soon be denied.
    ERR_UMODEUNKNOWNFLAG = 501, // ":Unknown MODE flag"
    ERR_USERSDONTMATCH = 502,   // ":Cannot change mode for other users"
    ERR_KEYSET = 467,           // "<channel> :Channel key already set"
    ERR_CHANNELISFULL = 471,    // "<channel> :Cannot join channel (+l)"
    ERR_UNKNOWNMODE = 472,      // "<char> :is unknown mode char to me for <channel>"
    ERR_INVITEONLYCHAN = 473,   // "<channel> :Cannot join channel (+i)"
    ERR_BANNEDFROMCHAN = 474,   // "<channel> :Cannot join channel (+b)"
    ERR_BADCHANNELKEY = 475,    // "<channel> :Cannot join channel (+k)"
    ERR_BADCHANMASK = 476,      // "<channel> :Bad Channel Mask"
    ERR_NOCHANMODES = 477,      // "<channel> :Channel doesn't support modes"
    ERR_BANLISTFULL = 478,      // "<channel> <char> :Channel list is full"
    ERR_NOPRIVILEGES = 481,     // ":Permission Denied- You're not an IRC operator"
                                // Any command requiring operator privileges to operate
                                // MUST return this error to indicate the attempt was
                                // unsuccessful.
    ERR_CHANOPRIVSNEEDED = 482, // "<channel> :You're not channel operator"
                                // Any command requiring 'chanop' privileges (such as
                                // MODE messages) MUST return this error if the client
                                // making the attempt is not a chanop on the specified
                                // channel.
    ERR_RESTRICTED = 484,       // ":Your connection is restricted!"
                                // Sent by the server to a user upon connection to indicate
                                // the restricted nature of the connection (user mode "+r").
    ERR_UNIQOPPRIVSNEEDED = 485,// ":You're not the original channel operator"
                                // Any MODE requiring "channel creator" privileges MUST
                                // return this error if the client making the attempt is not
                                // a chanop on the specified channel.
    // My own research
    RPL_NAMESLIST = 353, // :verne.freenode.net 353 G33kb0i = #tsukibot :G33kb0i @ChanServ OtakuSenpai
    OTHER = 999,

    // List of commands with no numeric replies:-
    // PING, JOIN, PRIVMSG
 };

  //const std::string Join = "JOIN";

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
    inline std::string getData() const{ return _data; }
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
    inline std::string getData() const { return _data; }
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
    inline std::string getData() const{ return _data; }
    inline std::vector<Nick> getUserList() const{ return chan_users; }
  };

  class Prefix {
  private:
    std::string _hostname;
    Nick _nick;
    User _user;
    bool _is_server = false;
    void Parse(const std::string& data);
  public:
    Prefix() : _hostname{}, _nick{}, _user{} {}
    Prefix(const std::string& data)
    {
      Parse(data);
    }
    ~Prefix() {}
    void operator= (const Prefix& obj);
    void setData(const std::string& data);
    void setNick(const std::string& nick);

    inline std::string getData() const {
      std::string temp;
      if(!_is_server)
        temp = _nick.getData() + "!" + _user.getData() + "@" + _hostname;
      else temp = _hostname;
      return temp;
    }
    inline std::string getNickData() const{ return _nick.getData(); }
    inline std::string getHostname() const{ return _hostname; }
    inline Nick getNick() const { return _nick; }
    inline User getUser() const{ return _user; }
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
      unsigned short port;

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

      inline void setUser(const std::string& obj) { user.setData(obj); }
      inline void setNick(const std::string& obj) { nick.setData(obj); }
      inline void setChan(const std::string& obj) { chan.setData(obj); }
      inline Nick getNick() const{ return nick; }
      inline Channel getChannel() const{ return chan; }
      inline User getUser() const{ return user; }
      inline std::string getRealName() const{ return realname; }
      inline std::string getPassword() const{ return pass; }
      inline unsigned int getPort() const{ return port; }
  };

} //namespace Tsuki

#endif



