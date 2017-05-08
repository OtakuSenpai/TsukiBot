#include "TsukiIRC.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>

void Tsuki :: Bot :: GetName(std::string& name)
{
	BotName = name;
	server_data.GetNick(BotName);
}	

bool Tsuki :: Bot :: has_alnum(std::string data)
{
   bool has_it = false,once = true;
   for(auto&& i = std::begin(data); i !=std::end(data); i++)
   {
       if(std::isalnum(*i))
       {   has_it = true;   }
       else if(!std::isalnum(*i))
       {   once = false;   }
   }
   if((has_it && once) || (!has_it && once))
   {   has_it = false;   }	
   return has_it;
}

bool Tsuki :: Bot :: has_only_spec(std::string data)
{
   std::vector<bool> values(data.size());
   bool has_it;
   for(size_t i = 0;i<data.size();i++)
   {
	  if(data[i] == '+' || data[i] == '-' || data[i] == '_' || data[i] == '=' || data[i] == '^' || data[i] == '*' ||
	     data[i] == '&' || data[i] == '(' || data[i] == ')' || data[i] == '%' || data[i] == '$' || data[i] == '#' ||
	     data[i] == '@' || data[i] == '!' || data[i] == '{' || data[i] == '[' || data[i] == '}' || data[i] == ']' ||
	     data[i] == '\\'|| data[i] == '|'|| data[i] == ':' || data[i] == ';' || data[i] == '"' || data[i] == '<' 
	     || data[i] == '>' || data[i] == '.' || data[i] == '?' || data[i] == '/')
	  {
	      values[i] = false;
	  }
	  else {   values[i] = true;   }
   }	   	
   for(auto&& i = std::begin(values); i != std::end(values); i++)
   {
	  if(*i == false)
	  {   has_it = true; }
   }
   values.clear();
   return has_it;
} 
	

bool Tsuki :: Bot :: has_only_space(std::string data)
{
   std::vector<bool> values(data.size());
   bool has_it;
   for(size_t i = 0;i<data.size(); i++)
   {
       if(data[i] == Tsuki::Space)
       { values[i] = false; }  
       else if(static_cast<bool>(std::isalpha(data[i])) == true || data[i] == static_cast<char>(95) ||
               data[i] == static_cast<char>(95) || data[i] == static_cast<char>(39) || data[i] == static_cast<char>(96) ||
               data[i] == '+' || data[i] == '@' || data[i] == ':' || data[i] == '[' || data[i] == ']' ||
               data[i] == '{' || data[i] == '}' || data[i] == '<' || data[i] == '_' || data[i] == '-' ||
               data[i] == '>' || data[i] == '^' || data[i] == '&' || data[i] == '*' || data[i] == '$' || 
               data[i] == '|' || data[i] == '\\' || data[i] == '/' )
       { values[i] = true; } 
       else { values[i] = true; }
   }
   for(auto&& i = std::begin(values); i != std::end(values); i++)
   {
	   if(*i == false)
	   { has_it = true; }
	   else
	   { has_it = false; }
   }
   values.clear();
   return has_it;
}
		   
bool Tsuki :: Bot :: begins_with(std::string message,const char* command)
{
   bool value = false; std::string temp1;
   temp1.assign(command);
   if(message.find(temp1) == 0)
   {
      std::string temp2 = message.substr(0,temp1.size());
      if(temp2.compare(command)==0)
      { value = true; }
      else
      { value = false; } 
   }
   return value;
}

bool Tsuki :: Bot :: has_it(std::string data,const char* command)
{
   std::vector<std::string> v;  bool ret = false;
   std::string comm{command};
   std::istringstream s(data);
   std::copy(std::istream_iterator<std::string>(s),
             std::istream_iterator<std::string>(),
             std::back_inserter(v));
   for(auto i: v)
   { 
	   if(i == comm)
	      ret = true;
   }
   v.clear();	             
   return ret;   
}
bool Tsuki :: Bot :: has_it(std::string data,char command)
{
   std::vector<std::string> v;  bool ret = false;
   std::string comm{command};
   std::istringstream s(data);
   std::copy(std::istream_iterator<std::string>(s),
             std::istream_iterator<std::string>(),
             std::back_inserter(v));
   for(auto i: v)
   { 
	   if(i == comm)
	      ret = true;
   }
	             
   return ret;   
}

std::string Tsuki :: Bot :: get_text_after_command(std::string message,const char* command)
{
	std::string temp;
	std::string comm{command};
	temp = message.substr(comm.size());
	return temp;
}

bool Tsuki :: Bot :: has_in_chan(std::string name,std::string& channel)
{
   bool has_it = false;
   for(auto&& i: chan_list)
   {   
	   if(channel == i.RetData())
       {   
          for(auto&& j: i.RetUser_List())
          {
	         if(name == j.RetData())
	         { has_it = true; break; }
	         else if(name == j.RetData().substr(1))
	         { has_it = true; break; }
	      }
	      if(has_it) { break; }
       }
       else continue;
   }
   std::cout<<std::endl<<"Has_in_chan: "<<has_it<<std::endl<<std::endl;
   return has_it; 
}		         	

void Tsuki :: Bot :: handle_msg(std::string& message)
{
	std::cout<<std::endl<<"Server Data: "<<message<<std::endl<<std::endl;
	segragrator(message, "\r\n"); message = "";
    message.clear();
	std::vector<std::string> tokens;
	std::string prefix,command,from,Priv_Comm,channel;
	std::string channels,temp,input;
	bool done = false;

	std::cout << "Size of msglogs: " << msglogs.size() << std::endl;

	for(auto&& z: msglogs)
	{
		bool prefix_found = false,sendr_found=false,comm_found = false;
   
		temp = z.c_str();
		std::istringstream c(temp);

		while(std::getline(c, input, ' ')) {
			tokens.push_back(input);
		}
	
		for(auto&& i: tokens)
		{ 
			if(!sendr_found)
			{
				if(i.find("#") == 0)
			    {   
			       from = i;
			       size_t j = chan_list.size();
			       if(j == 0 && command != "NOTICE" && command != "372")
			       { chan_list.push_back(Tsuki::Channel{from}); }
			       else { AddChannel(from,command); } 
			       sendr_found = true;
			    }  
				else if(command == "PRIVMSG" && i == RetName())
				{
				   from = prefix.substr(0,prefix.find("!"));
				   sendr_found = true;
			   }	
			}
			if(prefix_found && !sendr_found && !comm_found)
			{
				command = i;
				comm_found = true;
			}
			if((i.find(":") == 0) && (!prefix_found))
			{
				prefix = i.substr(1,i.size());
				prefix_found = true;
			}
			if((i.find(":") == 0) && (prefix_found) && (sendr_found) && (comm_found))
			{
				Priv_Comm = i.substr(1, i.size());
                
                if(command == "353" && from.at(0) == '#')
                {
				   bool found = false,colon1 = false;
				   std::string user;
				   for(auto&& j: tokens)
				   {
					  if((j.find(":") == 0) && (!colon1))
					  {
						 colon1 = true;
						 continue;
					  }
					  else if((j.find(":") == 0) && (colon1) && (!found))
					  {
					     found = true;
					  }
					  if(found)
					  {
					     user = j + " " + user;
					  } 
				   }
				   //std::cout<<std::endl<<"User: "<<user<<std::endl<<std::endl;
				   for(auto i =std::begin(chan_list); i != std::end(chan_list);i++)
				   {
					   //std::cout<<std::endl<<"In user list,from: "<<from<<std::endl<<std::endl;
				       if(i->RetData() == from)
				       { i->GetUsers(user); }
				   }
	               user.clear();
				}   	     
                std::cout<<"From: "<<from<<std::endl
                         <<"Comm: "<<command<<std::endl
                         <<"Prefix: "<<prefix<<std::endl
                         <<"Comm found: "<<comm_found<<std::endl
                         <<"Sendr found: "<<sendr_found<<std::endl
                         <<"prefix found: "<<prefix_found<<std::endl;
				if(Priv_Comm == ",join")
				{
					std::cout<<std::endl<<std::endl<<std::endl<<"In Join function...."<<std::endl<<std::endl<<std::endl;
					bool found = false;
					for(auto&& i: tokens)
					{
						if((i.find(":,join") != 0) && (!found))
						{
							continue;
						}
						else
						{
							found = true;
						}

						if(found)
						{ channels =  i + " " + channels ; }
					}
					std::istringstream x(channels); std::vector<std::string> chans;
					std::copy(std::istream_iterator<std::string>(x),
						std::istream_iterator<std::string>(),
						std::back_inserter(chans));
				    for(auto&& i: chans) std::cout<<i<<std::endl;
	                for(auto&& i: chans)
	                {
		               if(i.find("#") == 0)
		               {
		                  AddChannel(i,command);
		                  JoinChannel(i);
		                  done = true;
		                  break;
		               }
	                } 
	                chans.clear();	
	             }
	             else if(Priv_Comm == ",coffee")
		         {
					bool found = false;
					std::string temp;

					for(auto&& j: tokens)
					{
						if((j.find(":,coffee") != 0) && (!found))
						{
							continue;
						}
						else
						{
							found = true;
						}

						if(found)
						{
							temp = temp + " " + j;
						}
					}

					//std::istringstream d(temp);
					std::vector<std::string> user;//,tokens2;
					std::vector<Tsuki::Nick> n_user;
                    std::string s{":,coffee"},a;
                    bool isthere = false,hasatarget = false;
                    std::string target;
                      
				//	std::copy(std::istream_iterator<std::string>(d),
				//		std::istream_iterator<std::string>(),
				//		std::back_inserter(tokens2));
					a = temp.substr(s.size() + 2);
					if(a.size() < 2)
					{ isthere = false; }
					else
					{   
					   for(auto&& i = std::begin(a); i != std::end(a); i++)
					   {
					      if(std::isalnum(*i))
					      { isthere = true; }
				       }
				    }
				    std::cout<<std::endl<<"temp: "<<temp<<std::endl<<std::endl;
				    std::cout<<std::endl<<"isthere: "<<isthere<<std::endl<<std::endl;
				    std::cout<<std::endl<<"a: "<<a<<std::endl<<std::endl;
				    std::cout<<std::endl<<"a.size: "<<a.size()<<std::endl<<std::endl;
				    n_user = get_user_list(from);
				    for(auto&& i = std::begin(n_user); i != std::end(n_user); i++)
				       user.push_back(i->RetData());
				//  auto&& i = std::begin(tokens2);
				    auto&& j = std::begin(user);
					while(j != std::end(user))
					{
					   std::cout<<*j<<std::endl;	
				//	   while(i != std::end(tokens2))
				//	   {
					      if(a == "all")
					      { hasatarget = true; target.assign("all"); break; }
					      if(j->at(0) == '+' || j->at(0) == '@')
					      {
						     if(a == j->substr(1))
					         { hasatarget = true; target.assign(a); break; }
						  }
					      else if(a == *j) { hasatarget = true; target.assign(a); break; }
			    //	      i++;
				//	   }
				//	   i = std::begin(tokens2);
					   j++;
				    }
				    std::cout<<std::endl<<"hasatarget: "<<hasatarget<<std::endl<<std::endl;
				    std::cout<<std::endl<<"target: "<<target<<std::endl<<std::endl;
				    
				    if(from.find("#") == 0 || from.find("##") == 0)
				    {
				       if(a.size() != 0)
				       {
				          if(!has_in_chan(a,from) && !(a == "all" || a == RetName() || a == "herself"))
				          {
					         std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					         SendMe(temp,from); done = true; from.clear();
					      }
					      else if(isthere && has_it(a,Tsuki::Space))
					      {
					         std::string temp = "prepares a pile of shit for " + prefix.substr(0,prefix.find("!")) + ".";
					         SendMe(temp,from); done = true; from.clear();
					      }
					      else if(isthere && has_it(a,"shit"))
					      {
					         std::string temp = "prepares a pile of shit for " + prefix.substr(0,prefix.find("!")) + ".";
					         SendMe(temp,from); done = true; from.clear();
					      }
					      else if(isthere && ( has_it(a,RetName().c_str()) || has_it(a,"herself")))
					      {
					         std::string temp{"prepares a hot cup of coffee for herself and drinks it."};
					         SendMe(temp,from); done = true; from.clear();
					      }   
				          else if(has_it(a,Tsuki::Lf) || has_it(a,Tsuki::Cr) || has_it(a,Tsuki::Null))		
			              {
					         std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					         SendMe(temp,from); done = true; from.clear();
				          }
				          else if(!hasatarget || has_only_space(a))
				          {
					         std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					         SendMe(temp,from); done = true; from.clear();
				          }	   
				          else if(isthere && hasatarget)	
			              {  
				//	         for(auto&& k: tokens2)
			    //           {
				//			    std::cout<<std::endl<<"k: "<<k<<std::endl<<std::endl;
			                    if(target == "all")
			                    {
			                       std::string temp{"brews a hot cup of coffee for all."}; 
			                       SendMe(temp,from); done = true; from.clear();
			    //                 break;
			                    }
				                else if(hasatarget)  
				                {
			                        std::string temp = "brews a hot cup of coffee for " + target + "."; 
			                        SendMe(temp,from); done = true; from.clear();
			    //                 break;
				                } 	  
			    //           }
			              }
			          }   
				    }
				    else if(command == "PRIVMSG" && (has_in_chan(from,channel) || a == "herself" || a == RetName()))
				    { 
				       if(a.size() != 0)
				       {
				          if(isthere && ( has_it(a,RetName().c_str()) || has_it(a,"herself") ))
					      {
					         std::string temp{"prepares a hot cup of coffee for herself and drinks it."};
					         SendMe(temp,from); done = true; from.clear(); channel.clear();
					      }
					      else if(isthere)	
			              {  
					         std::cout<<std::endl<<"from: "<<from<<std::endl<<std::endl;
			                 std::string temp = "brews a hot cup of coffee for " + from + "."; 
			                 SendMe(temp,from); done = true; from.clear(); channel.clear();
			                 break; 	  
			              }   
				          else if(has_it(a,Tsuki::Lf) || has_it(a,Tsuki::Cr) || has_it(a,Tsuki::Null))		
			              {
							 std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					         SendMe(temp,from); done = true; from.clear(); channel.clear();
				          }	
				          else if(from != a && (!has_it(a,RetName().c_str()) || !has_it(a,"herself")))
				          {
						     std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					         SendMe(temp,from); done = true; from.clear(); channel.clear();	     
				          }
			           }
				    }   
				    else
				    {
						std::cout<<std::endl<<"In third condition: "<<std::endl<<std::endl;
					    std::string temp = "slaps " + prefix.substr(0,prefix.find("!")) + " for messing with her.";
					    SendMe(temp,from); done = true; from.clear();
				    }  
				    user.clear();
			//	    tokens2.clear();
			        a.clear();
			        target.clear(); 
			        temp.clear();
		          }
		    }      
		
		    if(done)
	        {
		       break;
		    }
	    }
		tokens.clear();
	}
	std::cout<<std::endl<<"Size of chan_list: "<<chan_list.size()<<std::endl<<std::endl;
    message.clear();
	msglogs.clear();
}

std::vector<Tsuki::Nick> Tsuki :: Bot :: get_user_list(std::string& from)
{
   std::vector<Tsuki::Nick> nick_list;
   bool isthere = false;
   for(auto&& i = std::begin(chan_list); i != std::end(chan_list); i++)
   {
	   if(i->RetData() == from)
	   {
		   nick_list = i->RetUser_List();
		   isthere = true;
		   std::cout<<std::endl<<"Found channel: "<<i->RetData()<<std::endl<<std::endl;
		   if(isthere) break;
	   }
   }
   return nick_list;
}    	

void Tsuki :: Bot :: segragrator(std::string& message,const char* data)
{
   size_t pos = 0;
	std::string token,delimiter{data};

	while ((pos = message.find(delimiter)) != std::string::npos) {
	    token = message.substr(0, pos);
	    msglogs.push_back(token);
	    message.erase(0, pos + delimiter.length());
	}
}
	      	

void Tsuki :: Bot :: Connect()
{
   std::string contents,command{"PING"};
   std::string serv_data,chan = "#cplusplus.com";
   running = false;
   bool connected = false,joined = false;
   
   //std::cout<<std::endl<<std::endl<<"In Zen::Bot::Connect...."<<std::endl;
   conn.Connect();
   
   if(!conn.isConnected())
   {
      std::cerr<<"Unable to connect to server!!! Retrying..."<<std::endl;
      conn.Connect();
      GetState(Tsuki::ServerState::SETTING_NICK);
   }
   GetState(Tsuki::ServerState::SETTING_NICK);
   running = true;
   
   if(RetState() == Tsuki::ServerState::SETTING_NICK)
   {   
      SendNick();
      std::cout<<"Nick sent..."<<std::endl;
      GetState(Tsuki::ServerState::SETTING_USER);
   }
   if(RetState() == Tsuki::ServerState::SETTING_USER)
   {
	  std::cout<<"Sending user..."<<std::endl;
	  SendUser(server_data.RetUserObj(),"Inuyasha",0);
	  std::cout<<"User sent..."<<std::endl;
	  GetState(Tsuki::ServerState::SETTING_PONG);
   }       
    
   std::cout<<"Entering loop...\n";
   while(conn.RecvData(serv_data) && IsRunning()) 
      {   
	     if(begins_with(serv_data,"PING"))
	     {
		    if(contents == "")
		    contents = serv_data.substr(command.size());
		    SendPong(contents);
		    GetState(Tsuki::ServerState::WORKING); connected = true;
	     }  	 
	     if(has_it(serv_data,"004"))
	     {
			 std::cout<<std::endl<<"Connected!!!"<<std::endl<<std::endl;
			 connected = true;
		 }
		 if(has_it(serv_data,"433"))
	     {
			 std::string nick = "DsJki";
			 SendNick(nick);
		 }
	     if(connected == true && joined == false)
	     {
		    JoinChannel(chan); joined = true;
		 }
		 if(RetState() == Tsuki::ServerState::SETTING_PONG || begins_with(serv_data,"PING"))
         {
	        if(contents == "")
	        contents = serv_data.substr(command.size());
            SendPong(contents);
            GetState(Tsuki::ServerState::WORKING);
         } 	 
	     handle_msg(serv_data);
	     serv_data.clear();
      }         	  	  
  std::cout<<"Exiting Zen::Bot::Connect....\n";
}

void Tsuki :: Bot :: Disconnect()
{
	conn.DisConnect();
	GetState(Tsuki::ServerState::NOT_CONNECTED);
}

void Tsuki :: Bot :: JoinChannel(Channel& chan)
{
        std::string data = std::string{"JOIN "} + chan.RetData() + std::string{"\r\n"};
        conn.SendData(data);
}   

void Tsuki :: Bot :: JoinChannel(std::string& channel)
{
        std::string data = std::string{"JOIN "} + channel + std::string{"\r\n"};
        conn.SendData(data);
}

void Tsuki :: Bot :: SendMsg(std::string& msg)
{
	conn.SendData(msg);
}

void Tsuki :: Bot :: SendMsg(const char* command,std::string& msg)
{
	std::string s = std::string(command) + " :" + msg;
	conn.SendData(s);
}

void Tsuki :: Bot :: SendNick()
{ 
        std::string s; 
        s = "NICK " + BotName + "\r\n"; 
        std::cout<<"Nick: "<<s<<std::endl;
        conn.SendData(s);
}   

void Tsuki :: Bot :: SendNick(std::string& nick)
{ 
        std::string s; 
        s = "NICK " + nick + "\r\n"; 
        conn.SendData(s);
}

void Tsuki :: Bot :: SendUser(User user,std::string& realname,int mode)
{
        std::string s = "USER " + user.RetData() + " " + std::to_string(mode) + " :" + realname + "\r\n";
        conn.SendData(s);
} 
			
void Tsuki :: Bot :: SendUser(User user,const char* realname,int mode)
{   
   std::string s = "USER " + user.RetData() + " " + std::to_string(mode) + " *" + " :" + std::string(realname) + "\r\n";
   std::cout<<"Sending user: "<<s<<std::endl;
   conn.SendData(s);
}

void Tsuki :: Bot :: SendMe(std::string& message,std::string& target)
{
   std::string temp = "PRIVMSG " + target + " :\001ACTION " + message + "\001\r\n";
   std::cout<<std::endl<<std::endl<<std::endl<<"Sending /me : "<<temp<<std::endl<<std::endl<<std::endl;
   conn.SendData(temp);
}

void Tsuki :: Bot :: SendPong(std::string& contents)
{
   std::string temp = "PONG " + contents + "\r\n";
   conn.SendData(temp);
}	

void Tsuki :: Bot :: AddChannel(std::string& channel,std::string& command)
{
   size_t j = chan_list.size();
   //std::cout<<std::endl<<"Chan size in AddChannel: "<<j<<std::endl<<std::endl;
   bool has_chan = false,chan_is_not_command = false;
   std::string from = channel;
   if(j == 0 )
   {
      if(command == "372" || command == "NOTICE" || from == "#freenode" || from == "##Linux" || command != "PRIVMSG")
	  { from = ""; chan_is_not_command = true; }
	  else  	
	  { Tsuki::Channel a{from}; chan_list.push_back(a); from = ""; }
   }
   else if(j > 0)
   {
	  if(command == "372" || command == "NOTICE" || from == "#freenode" ||  command != "PRIVMSG")
	  { from = ""; chan_is_not_command = true; }
	  for(auto i = std::begin(chan_list); i != std::end(chan_list); i++)
	  {
	     size_t k = std::distance(std::begin(chan_list),i);
		 if(k > j) break;
		 if(i->RetData() == from)
		 { has_chan = true; } 
	  }
	  if(!has_chan)
      { 
         if(!chan_is_not_command)   
	     { Tsuki::Channel a{from}; chan_list.push_back(a); }
      }
   }
   //std::cout<<std::endl<<"Channels are: "<<std::endl;
   //for(auto i: chan_list) std::cout<<i.RetData()<<std::endl;
}
