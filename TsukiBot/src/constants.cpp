#include <stdexcept>
#include <iterator>
#include <iostream>

#include "constants.hpp"

void Tsuki :: Nick :: operator= (const Nick& obj) {
  _data = std::move(obj._data);
  Parse();
}
void Tsuki :: Nick :: setData(const std::string& data) {
  _data = data;
  Parse();
}

void  Tsuki :: Nick :: Parse() {
  try {
    int i = 0;
    if(static_cast<bool>(std::isalpha(_data[0])) == false &&
      (_data[0] != static_cast<char>(95) && _data[1] != static_cast<char>(95)) &&
       _data[0] != '+' && _data[0] != '@' && _data[0] != ':' && _data[0] != '[' && _data[0] != ']' &&
       _data[0] != static_cast<char>(39) && _data[0] != '{' && _data[0] != '}' && _data[0] != '<' &&
       _data[0] != '>' && _data[0] != '^' && _data[0] != '&' && _data[0] != '*' && _data[0] != '$'
       && _data[0] != static_cast<char>(96) && _data[0] != '|' && _data[0] != '\\' && _data[0] != '/' ) {
      std::cout<<_data<<std::endl;
      throw std::runtime_error("constants.cpp : In Tsuki::Nick::Parse() : First character of a nick can't be non-alpha.\n");
    }
    for(auto iter = _data.begin(); iter != _data.end(); iter++) {
      i = std::distance(_data.begin(),iter);
      if(_data[i] == static_cast<char>(95)  || ((bool) std::isalnum(_data[i]) == true )  ||
        ((bool) std::isdigit(_data[i]) == true ))
        continue;
      else if(static_cast<bool>(std::isalpha(_data[i])) == true || _data[i] == static_cast<char>(95) ||
        _data[i] == static_cast<char>(95) || _data[i] == static_cast<char>(39) || _data[i] == static_cast<char>(96) || _data[i] == '+' || _data[i] == '@' || _data[i] == ':' || _data[i] == '[' || _data[i] == ']' ||
        _data[i] == '{' || _data[i] == '}' || _data[i] == '<' || _data[i] == '_' || _data[i] == '-' ||
        _data[i] == '>' || _data[i] == '^' || _data[i] == '&' || _data[i] == '*' || _data[i] == '$' ||
        _data[i] == '|' || _data[i] == '\\' || _data[i] == '/' )
        continue;
      else if(_data[i] == Tsuki::Dash || _data[i] == Tsuki::LeftSquareBrackets ||
        _data[i] == Tsuki::RightSquareBrackets || _data[i] == Tsuki::LeftSlash ||
        _data[i] == Tsuki::SingleQuote || _data[i] == Tsuki::Power ||
        _data[i] == Tsuki::LeftCurlyBraces  || _data[i] == Tsuki::RightCurlyBraces)
        continue;
      else if(_data[i] == Tsuki::Space || _data[i] == Tsuki::Null ||
        _data[i] == Tsuki::Lf || _data[i] == Tsuki::Cr || _data[i] == ',' ) {
        std::string temp = "constants.cpp : In Tsuki::Nick::Parse() : Can't have '" + std::string{_data.at(i)} +"' in Nick.\n";
        throw  std::runtime_error(temp);
      }
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: Channel :: operator= (const Channel& obj) {
  _data = std::move(obj._data);
  Parse();
}

void Tsuki :: Channel :: setData(const std::string& data) {
  _data = data;
  Parse();
}

void Tsuki :: Channel :: setUsers(const std::string& list) {
  try {
    size_t pos = 0;
    std::string token,delimiter{" "},tempValue;
    tempValue = list;
    while((pos = tempValue.find(delimiter)) != std::string::npos) {
      token = tempValue.substr(0,pos);
      chan_users.push_back(Nick{token});
      tempValue.erase(0,pos + delimiter.size());
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: Channel  :: Parse() {
  try {
    int i = 0;
    if(_data[0] != '#' && _data[0] != '&' ) {
      throw std::runtime_error("constants.cpp : In Tsuki::Channel::Parse() : First character of a channel must be '#' or '&'.\n");
    }
    for(auto iter = _data.begin(); iter != _data.end(); iter++) {
      i = std::distance(_data.begin(),iter);
      if(_data[i] == '-' || _data[i] == '_') continue;
      if(_data[i]  == Tsuki::Space || _data[i] == Tsuki::Null ||
         _data[i] == Tsuki::Lf || _data[i] == Tsuki::Cr || _data[i] == ',' )
        throw  std::runtime_error("constants.cpp : In Tsuki::Channel::Parse() : Can't have any space,comma,null character, carriage return or newline in Channel.\n");
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: User :: operator= (const User& obj) {
  _data = std::move(obj._data);
  Parse();
}

void Tsuki :: User :: setData(const std::string& data) {
  _data = data;
  Parse();
}

void Tsuki :: User :: Parse() {
  try {
    int i = 0;
    for(auto iter = _data.begin(); iter != _data.end(); iter++) {
      i = std::distance(_data.begin(),iter);
      if( (bool) std::isalpha(_data[i]) || (bool) std::isdigit(_data[i]) )
        continue;
      else if(_data[i] == Tsuki::Dash || _data[i] == Tsuki::LeftSquareBrackets ||
        _data[i] == Tsuki::RightSquareBrackets || _data[i] == Tsuki::LeftSlash ||
        _data[i] == Tsuki::SingleQuote || _data[i] == Tsuki::Power ||
        _data[i] == Tsuki::LeftCurlyBraces  || _data[i] == Tsuki::RightCurlyBraces)
        continue;
      else  {
        std::string temp = "constants.cpp : In Tsuki::User::Parse() : Can't have a '" + std::string{_data.at(i)} + "' in the User field.\n";
        throw std::runtime_error(temp);
      }
    }
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}

void Tsuki :: Prefix :: operator= (const Prefix& obj) {
  _hostname = std::move(_hostname);
  _nick = obj._nick;
  _user = obj._user;
}

void Tsuki :: Prefix :: setData(const std::string& data) {
  Parse(data);
}

void Tsuki :: Prefix :: setNick(const std::string& nick) {
  _nick.setData(nick);
}

void Tsuki :: Prefix :: Parse(const std::string& _data) {
  try {
    int i = 0;
    std::string temp;
    if( _data[0] != ':' ) {
      temp = "constants.cpp : In Tsuki::Prefix::Parse() : Problem parsing prefix,bad source to parse: " + _data + ".\n";
      throw std::runtime_error(temp);
    }
    bool foundasterisk = false,foundexclam = false;
    for(auto iter1 = _data.begin(); iter1 != _data.end(); iter1++) {
      i = std::distance(_data.begin(),iter1);
      if(_data[i] == '!' ) {
        temp = _data.substr(1,i-1);
        _nick.setData(temp);
        foundexclam = true;
        temp = _data.substr(i+2);
        break;
      }
      else continue;
    }
    i=0;  std::string refstr;
    for(auto iter2 = temp.begin(); iter2 != temp.end(); iter2++) {
      i = std::distance(temp.begin(),iter2);
      if( temp[i] == '@' ) {
        refstr = temp.substr(0,i);
        _user.setData(refstr);  foundasterisk = true;
        _hostname = temp.substr(i+1);
      }
    }
    if(foundasterisk == false)
      throw std::runtime_error("constants.cpp : In Tsuki::Prefix::Parse() : Problem parsing prefix,didnt find the nick.\n");
    if(foundexclam == false)
      throw std::runtime_error("constants.cpp : In Tsuki::Prefix::Parse() : Problem parsing prefix,didnt find the hostname and username.\n");
  }
  catch(std::exception& e) {
    std::cout<<"Caught exception : \n"<<e.what();
  }
}
