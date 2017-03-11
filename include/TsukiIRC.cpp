#include "TsukiIRC.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

void Tsuki :: Bot :: GetName(std::string& name)
{
	BotName = name;
	server_data.GetNick(BotName);
}

bool Tsuki :: Bot :: begins_with(std::string& message,const char* command)
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

bool Tsuki :: Bot :: has_it(std::string& data,const char* command)
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

std::string Tsuki :: Bot :: get_text_after_command(std::string& message,const char* command)
{
	std::string temp;
	std::string comm{command};
	temp = message.substr(comm.size());
	return temp;
}

void Tsuki :: Bot :: handle_msg(std::string& message)
{
	segragrator(message,"\r\n");
	
	std::vector<std::string> tokens;
	std::string prefix,command,from,Priv_Comm;
	std::string channels,temp,input;
	
	bool prefix_found = false,sendr_found=false,comm_found = false;
	bool done = false;
	
	for(auto&& z: msglogs)
	{
		if(done)
		{ break; }
		temp = z.c_str();
		std::istringstream c(temp);
		if(done)
		{ break; } 
		while(std::getline(c,input,' '))
		   tokens.push_back(input);
		for(auto i: tokens)
		{ 
		   if((i.find(":") == 0) && (prefix_found) && (sendr_found) && (comm_found))
		   {   
		      Priv_Comm = i.substr(1,i.size());
		      if(Priv_Comm == ",join")
	          {
		         bool found = false;
		         for(auto&& i: tokens)
	             {
		            if((i.find(":,join") != 0) && (!found))
		            {  
			           continue;
		            } 
		            else { found = true; }
		            if(found)
		            {
		               channels =  i + " " + channels ;
		            }
	             }
	             std::istringstream x(channels); std::vector<std::string> chans;
	             std::copy(std::istream_iterator<std::string>(x),
	                    std::istream_iterator<std::string>(),
	                    std::back_inserter(chans));
	             for(auto&& i: chans)
	             {
		            if(i.find("#") == 0)
		            {
		               AddChannel(i);
		               JoinChannel(i);
		               done = true;
		               break;
		            }
		            if(done)
		            { break; }
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
				 { continue; }
				 else 
				 { found = true; }
				 if(found)
				 {
					temp = j + " " +temp;
				 }
			  }
			  std::cout<<std::endl<<std::endl<<std::endl<<"Temp is: "<<temp<<std::endl<<std::endl<<std::endl;
			  std::cout<<std::endl<<std::endl<<std::endl<<"From is: "<<from<<std::endl<<std::endl<<std::endl;
			  std::cout<<std::endl<<std::endl<<std::endl<<"Command is: "<<command<<std::endl<<std::endl<<std::endl;
			  std::cout<<std::endl<<std::endl<<std::endl<<"Prefix is: "<<prefix<<std::endl<<std::endl<<std::endl;
			  std::istringstream d(temp); std::vector<std::string> tokens2;
			  std::copy(std::istream_iterator<std::string>(d),
			            std::istream_iterator<std::string>(),
			            std::back_inserter(tokens2));
			  for(auto&& k: tokens2)
			  {
			     if(k == "all")
			     {
			        std::string temp{"brews a hot cup of coffee for all."}; 
			        SendMe(temp,from); done = true; from.clear();
			        break;
			     }
				 else 
				 {
			        std::string temp = "brews a hot cup of coffee for " + k + "."; 
			        SendMe(temp,from); done = true; from.clear();
			        break;
				 }
				 if(done)
		         { break; }	  
			  }
			  tokens2.clear();
			  temp.clear();
		   }
		}      
		
		if(!sendr_found && (std::isalnum(i.at(0)) || (i.find("#")==0) ) && comm_found) 
		{ 
		    from = i.substr(1,i.size());
		    sendr_found = true; 
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
     }
	tokens.clear();
	}	
}

void Tsuki :: Bot :: segragrator(std::string& message,const char* data)
{
   std::string temp;
   std::string::size_type pos = 0, prev = 0;
   temp.assign(data);
   
   while((pos = message.find(temp,prev)) != std::string::npos)
   {
	  msglogs.push_back(message.substr(prev,pos-prev));
	  prev = pos +1;
   }
}
	      	

void Tsuki :: Bot :: Connect()
{
   std::string contents,command{"PING"};
   std::string serv_data,chan = "#cplusplus.com";
   running = false;
   bool connected = false,joined = false,receiving = false;
   
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
    
   std::cout<<"Entering loop...\n";
   while(conn.RecvData(serv_data) && IsRunning()) 
      {   
         std::cout<<"Server Data: "<<std::endl<<serv_data<<std::endl;
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
         if(RetState() == Tsuki::ServerState::SETTING_PONG || begins_with(serv_data,"PING"))
         {
		    if(contents == "")
		    contents = serv_data.substr(command.size());
		    SendPong(contents);
		    GetState(Tsuki::ServerState::WORKING); connected = true;
	     }
	     if(begins_with(serv_data,"PING"))
	     {
		    if(contents == "")
		    contents = serv_data.substr(command.size());
		    SendPong(contents);
		    GetState(Tsuki::ServerState::WORKING); connected = true;
	     }
	     if(connected == true && joined == false)
	     {
		    JoinChannel(chan); joined = true;
		 } 	 
		 if(connected == true && joined == true && (!receiving) )
		 {
			 serv_data.clear();
			 receiving = true;
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

void Tsuki :: Bot :: AddChannel(std::string& channel)
{
   chan_list.emplace_back(Tsuki::Channel(channel));
}
