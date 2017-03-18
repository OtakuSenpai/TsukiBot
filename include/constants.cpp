#include <stdexcept>
#include <iterator>
#include <iostream>

#include "constants.hpp"

/*
void Zen :: Mask :: Parse()
{
    int i = 0;
    if(_data[0] != '#' || _data[0] != '$' )
       throw std::runtime_error{"ZenIRC Error: Need to have first character of Mask as '#' or '$'. "};	    
    for(auto iter = _data.begin(); iter!=_data.end(); iter++)
    {
	i = std::distance(_data.begin(),iter);
        if( _data[i] == Zen::Space || _data[i] == Zen::Null || _data[i] == Zen::Lf || _data[i] == Zen::Cr || _data[i] == ',' )
           throw std::runtime_error{"ZenIRC Error: Space or null or Left return or carriage return not allowed in User field."}; 	
    }
}    
*/

void Tsuki :: Nick :: operator= (const Nick& obj)
{
   _data = obj.RetData();
   Parse();
}
void Tsuki :: Nick :: GetData(std::string& data)
{
   _data = data;
   Parse();
}

void  Tsuki :: Nick:: Parse()
{
     int i = 0;
     if(static_cast<bool>(std::isalpha(_data[0])) == false && 
        (_data[0] != static_cast<char>(95) && _data[1] != static_cast<char>(95)) && 
        _data[0] != '+' && _data[0] != '@' && _data[0] != ':' && _data[0] != '[' && _data[0] != ']' &&
        _data[0] != static_cast<char>(39) && _data[0] != '{' && _data[0] != '}' && _data[0] != '<' && 
        _data[0] != '>' && _data[0] != '^' && _data[0] != '&' && _data[0] != '*' && _data[0] != '$'
        && _data[0] != static_cast<char>(96) && _data[0] != '|' && _data[0] != '\\' && _data[0] != '/' )
     {
		 std::cout<<_data<<std::endl;
        throw std::runtime_error{"ZenIRC Error: First character of a nick can't be non-alpha."};
     } 	     
     for(auto iter = _data.begin(); iter != _data.end(); iter++)
     {
        i = std::distance(_data.begin(),iter);
        if(_data[i] == static_cast<char>(95)  || ((bool) std::isalnum(_data[i]) == true )  ||  
          ((bool) std::isdigit(_data[i]) == true ))
           continue;
        else if(static_cast<bool>(std::isalpha(_data[i])) == true || _data[i] == static_cast<char>(95) ||
               _data[i] == static_cast<char>(95) || _data[i] == static_cast<char>(39) || _data[i] == static_cast<char>(96) ||
               _data[i] == '+' || _data[i] == '@' || _data[i] == ':' || _data[i] == '[' || _data[i] == ']' ||
               _data[i] == '{' || _data[i] == '}' || _data[i] == '<' || _data[i] == '_' || _data[i] == '-' ||
               _data[i] == '>' || _data[i] == '^' || _data[i] == '&' || _data[i] == '*' || _data[i] == '$' || 
               _data[i] == '|' || _data[i] == '\\' || _data[i] == '/' ) 
           continue;  		
        else if(_data[i] == Tsuki::Dash || _data[i] == Tsuki::LeftSquareBrackets ||  
                _data[i] == Tsuki::RightSquareBrackets || _data[i] == Tsuki::LeftSlash || 
                _data[i] == Tsuki::SingleQuote || _data[i] == Tsuki::Power || 
                _data[i] == Tsuki::LeftCurlyBraces  || _data[i] == Tsuki::RightCurlyBraces)
            continue;
	else if(_data[i] == Tsuki::Space || _data[i] == Tsuki::Null || _data[i] == Tsuki::Lf || _data[i] == Tsuki::Cr || _data[i] == ',' )
	    throw  std::runtime_error{"ZenIRC Error: Can't have any space,comma,null character, carriage return or newline in Nick."};
      }
}

void Tsuki :: Channel :: operator= (const Channel& obj)
{
   _data = obj.RetData();
   Parse();
}

void Tsuki :: Channel :: GetData(std::string& data)
{
   _data = data;
   Parse();
}

void Tsuki :: Channel :: GetUsers(std::string& list)
{
   size_t pos = 0;
   std::string token,delimiter{" "};
   while((pos = list.find(delimiter)) != std::string::npos)
   {
	   token = list.substr(0,pos);
	   chan_users.push_back(Nick{token});
	   list.erase(0,pos + delimiter.size());
   }
}
   
void Tsuki :: Channel  :: Parse()
{
   int i = 0;
   if(_data[0] != '#' && _data[0] != '&' )
   {  
	  throw std::runtime_error{"ZenIRC Error: First character of a channel must be '#' or '&'. "}; 
   }     
   for(auto iter = _data.begin(); iter != _data.end(); iter++)
   {
      i = std::distance(_data.begin(),iter);
      if(_data[i] == '-' || _data[i] == '_') continue;
      if(_data[i]  == Tsuki::Space || _data[i] == Tsuki::Null || 
         _data[i] == Tsuki::Lf || _data[i] == Tsuki::Cr || _data[i] == ',' )
        throw  std::runtime_error{"ZenIRC Error: Can't have any space,comma,null character, carriage return or newline in Channel."};
    }  
   
}	

void Tsuki :: User :: Parse()
{
	int i = 0;
	for(auto iter = _data.begin(); iter != _data.end(); iter++)
	{
	    i = std::distance(_data.begin(),iter);
	    if( (bool) std::isalpha(_data[i]) || (bool) std::isdigit(_data[i]) )
	       continue;
	    else if(_data[i] == Tsuki::Dash || _data[i] == Tsuki::LeftSquareBrackets ||  _data[i] == Tsuki::RightSquareBrackets || _data[i] == Tsuki::LeftSlash || _data[i] == Tsuki::SingleQuote || _data[i] == Tsuki::Power || _data[i] == Tsuki::LeftCurlyBraces  || _data[i] == Tsuki::RightCurlyBraces)
               continue;
	    else
	       throw std::runtime_error{"ZenIRC Error: Can't have a \" _data[i]\" in the User field."}; 	    
	}
}

void Tsuki :: Prefix :: Parse()
{
   int i = 0;
   std::string temp;
   if( _data[0] != ':' )
   { 
	  temp = "ZenIRC Error: Problem parsing prefix,bad source to parse: " + _data;
      throw std::runtime_error{temp};
   }
   bool foundasterisk = false,foundexclam = false;
   for(auto iter1 = _data.begin(); iter1 != _data.end(); iter1++)
   {
	  i = std::distance(_data.begin(),iter1);	
      if(_data[i] == '!' )
	  {	
		 temp = _data.substr(0,i);
		 _nick.GetData(temp);   foundexclam = true;
		 temp = _data.substr(i+1);
         break; 
	  }
      else continue;  
   }
   i=0;  std::string refstr;
   for(auto iter2 = temp.begin(); iter2 != temp.end(); iter2++)
   {
	  i = std::distance(temp.begin(),iter2);
	  if( temp[i] == '@' )
	  {
		 refstr = temp.substr(0,i);
		 _user.GetData(refstr);  foundasterisk = true;
		 _hostname = temp.substr(i+1);
	  }
   }
   if(foundasterisk == false)
	  throw std::runtime_error{"ZenIRC Error: Problem parsing prefix,didnt find the nick."};
   if(foundexclam == false)
	  throw std::runtime_error{"ZenIRC Error: Problem parsing prefix,didnt find the hostname and username."}; 	
}   					

std::string Tsuki :: Irc_Data :: RetSParameters()          	
{
   std::string temp;
   for(auto iter = std::begin(parameters); iter != std::end(parameters); iter++)
   { temp = temp + " " + *iter; }
   return temp;
}  	   

void Tsuki :: Irc_Data :: operator=(const Irc_Data& obj)
{
   command = obj.command;
   parameters = obj.parameters;
   prefix = obj.prefix;
}
