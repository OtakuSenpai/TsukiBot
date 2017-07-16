#include "ircmessage.hpp"


Tsuki :: IRCMessage :: IRCMessage(const IRCMessage& obj)
{
  _sender = obj.getSender();
  msg_data = obj.getMsgData();
}

void Tsuki :: IRCMessage :: Parse(std::string& data)
{
  auto front = data.begin();
  auto end = data.end();

  if(*front == ':') {
    auto prefix = std::find(++front,end,' ');
    _sender.assign(front,prefix);
    msg_data.prefix.setData(_sender);
    front = safe_iterate(front,prefix);
  }
  else {
    std::string a ="";
    msg_data.prefix.setData(a);
  }
  auto command = std::find(front,end,' ');
  msg_data.command.assign(front,command);
  front = safe_iterate(front,command);

	/*
	if( (temp2.compare("PASS") || temp2.compare("pass")) || (temp2.compare("NICK") || temp2.compare("nick"))  ||
	    (temp2.compare("USER") || temp2.compare("user")) || (temp2.compare("OPER") || temp2.compare("oper")) ||
	    (temp2.compare("MODE") || temp2.compare("mode")) || (temp2.compare("QUIT") || temp2.compare("quit")) ||
	    (temp2.compare("SQUIT") || temp2.compare("squit")) ||  (temp2.compare("JOIN") || temp2.compare("join")) ||
	    (temp2.compare("PART") || temp2.compare("part")) || (temp2.compare("TOPIC") || temp2.compare("topic")) ||
	    (temp2.compare("NAMES") || temp2.compare("names")) || (temp2.compare("LIST") || temp2.compare("list")) ||
	    (temp2.compare("INVITE") || temp2.compare("invite")) || (temp2.compare("KICK") || temp2.compare("kick")) ||
	    (temp2.compare("PRIVMSG") || temp2.compare("privmsg")) || (temp2.compare("MSG") || temp2.compare("msg")) ||
	    (temp2.compare("NOTICE") || temp2.compare("notice")) || (temp2.compare("MOTD") || temp2.compare("motd")) )
	    {
		IsACommand = true;
		msg_data.command = temp2;
	    }

	else
	{
		IsACommand = false;
	}
	*/
  std::string temp;
  while(front != end) {
    auto params = std::find(front,end,' ');
    if(params == std::end(data)) params = std::find(front,end,',');
    temp.assign(front,params);
    msg_data.parameters.push_back(temp); temp.clear();
    front = safe_iterate(front,params);
  }
}



Irc_Data Tsuki :: IRCMessage :: dataParse(std::string& data)
{
  Parse(data);
  return msg_data;
}


