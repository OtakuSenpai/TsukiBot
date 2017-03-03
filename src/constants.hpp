#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#pragma once

#include <string>
#include <vector>

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
static const std::string RPL_LIST = "322";
static const std::string RPL_LISTEND = "323";
static const std::string RPL_ENDOFMOTD = "376";
static const std::string ERR_NOSUCHNICK = "401";
static const std::string ERR_NOSUCHSERVER = "402";
static const std::string ERR_NOSUCHCHANNEL = "403";
static const std::string ERR_CANNOTSENDTOCHAN = "404";
static const std::string ERR_TOOMANYCHANNELS = "405";
static const std::string ERR_WASNOSUCHNICK = "406";
static const std::string ERR_TOOMANYTARGETS = "407";
static const std::string ERR_NOORIGIN = "409";
static const std::string ERR_NORECIPIENT = "411";
static const std::string ERR_NOTEXTTOSEND = "412";
static const std::string ERR_NOTOPLEVEL = "413";

static const std::string Join = "JOIN";

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
class User
{
private:	
   std::string _data;
   void Parse(); 

public:
   User() : _data{} {}
   User(std::string& data) : _data(data) { Parse(); }
   void operator= (const User& obj)
   {
      _data = obj.RetData();
	  Parse();
   }
   void GetData(std::string& data)
   {
	  _data = data;
	  Parse();
   }
   std::string RetData() const{ return _data; }
   ~User() {}
};

/* Nick class stores the nickname of a connection to the network.
 * Used in Prefix class and Join_Data struct.
 */
class Nick
{
private:
       std::string _data;  	
       void Parse(); 

public:
	Nick() : _data{} {}
        Nick(std::string& data) : _data(data) { Parse(); }
	void operator= (const Nick& obj)
	{
		_data = obj.RetData();
		Parse();
	}
	void GetData(std::string& data)
       {
	      _data = data;
	      Parse();
       }
       std::string RetData() const { return _data; }
	~Nick() {}
};

class Channel
{
private:
      std::string _data;
      void Parse();

public:
      Channel() : _data{} {}	
      Channel(std::string& data): _data(data) { Parse(); }
      void operator= (const Channel& obj)
	{
		_data = obj.RetData();
		Parse();
	}
      void GetData(std::string& data)
      {
	      _data = data;
	      Parse();
      }
      std::string RetData() const{ return _data; }
      ~Channel() {}
};

//obsolete
/*
class Mask
{
private:
      std::string _data;
      void Parse();
public:
      Mask() = default;
      Mask(std::string& data):  _data(data) { Parse(); }
      void GetData(std::string& data)
      {
	      _data = data;
	      Parse();
      }
      void operator= (const Mask& obj)
	{
		_data = obj.RetData();
		Parse();
	}
      std::string RetData() { return _data; }
      ~Mask() {}
};
*/

/* The Prefix class stores the data of the sender in its data members.
 * Its used in the Irc_Data struct. 
 */
class Prefix
{
private:
      std::string _data,_hostname,_ident;	
      Nick _nick; 
      User _user;
      void Parse();
 public:
      Prefix() : _data{}, _hostname{}, _ident{}, _nick{}, _user{} {}
      Prefix(std::string& data): _data(data) { Parse(); }
      void operator= (const Prefix& obj)
      {
	      _data = obj.RetData();
	      _hostname = obj.RetHostname();
	      _nick = obj.RetNick();
	      _user = obj.RetUser();
	      _ident = obj.RetIdent();
      }
      
      void GetData(std::string& data)
      {
	      _data = data;
	      Parse();
      }
      void GetNick(std::string& nick)
      {
	      _nick.GetData(nick);
      }
      std::string RetData() const { return _data; }
      std::string RetNickData() { return  _nick.RetData(); }
      std::string RetHostname() const{ return _hostname; }
      std::string RetIdent() const{ return _ident; }
      Nick RetNick() const { return _nick; }
      User RetUser() const{ return _user; }       
};

/* This struct is used in sending data through the IRC.
 * Used in IRCMessage class.
 */
struct  Irc_Data 
{  
	Prefix prefix;  //  nick!username@host
	std::string command;   // the commands	
	std::vector<std::string> parameters;  //   the parameters to the command
	                                  
	Irc_Data() : prefix{}, command{}, parameters{} {}
	Irc_Data(std::string& pref,std::string& comm): prefix{pref}, command{comm} {}
	Irc_Data(std::string& pref,const char* comm): prefix{pref}, command{comm} {}
	~Irc_Data() {}

	void operator=(const Irc_Data& obj)
	{
		command = obj.command;
		parameters = obj.parameters;
		prefix = obj.prefix;
	}
	 
          
	std::string RetPrefix() { return prefix.RetData(); }
	std::string RetCommand() { return command; }
	std::vector<std::string> RetParameters() { return parameters; }	
        std::string RetSParameters() 
        {
		std::string temp;
		for(auto iter = parameters.rbegin(); iter != parameters.rend(); iter++)
                 {
			temp = temp + " " + *iter; 
                 }
		 return temp;
	 }
         void GetPrefix(std::string& pref) { prefix.GetData(pref); } 
         void GetCommand(std::string& obj) { command = obj; }  
};	

/* This struct is used in joining to a given channel.
 * Used in IRCConnector class.
 */
struct  Join_Data
{ 
	std::string server;
	Channel chan;
	Nick nick;
	User user;
	std::string pass;
	unsigned int port;
        
        Join_Data() : server{}, chan{}, nick{}, user{}, pass{}, port{6667} {}
	Join_Data(std::string& serv,std::string& channel,std::string& nickname,
		       std::string& username,std::string& password,
	               unsigned int& p) : chan{channel}, nick{nickname}, user{username}
	{
		server = serv;
		pass = password;
		port =p;
	}
		
	~Join_Data() {}
    std::string RetNick() { return nick.RetData(); }
	void GetNick(std::string& obj) { nick.GetData(obj); } 
    std::string RetChan() { return chan.RetData(); }
	void GetChan(std::string& obj) { chan.GetData(obj); }
    std::string RetUser() { return user.RetData(); }
    User RetUserObj() { return user; }   
    void GetUser(std::string& obj) { user.GetData(obj); }    	
};

struct A { Nick nick;
		  Channel chan;	 
		  std::string flags;  
		  A* next; };
using chan_user_list = struct A;

}		

#endif
						   
						   
						   
