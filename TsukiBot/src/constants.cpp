#include <stdexcept>
#include <iterator>
#include <iostream>
#include <sstream>

#include "constants.hpp"

void Tsuki :: Nick :: operator= (const Nick& obj) {
  _data = std::move(obj._data);
  Parse();
}
void Tsuki :: Nick :: setData(const std::string& data) {
  _data = data;
  Parse();
}

std::string Tsuki :: Nick :: getData() const { 
  return _data; 
}

void Tsuki :: Nick :: clear() {
  _data.clear();
}

void  Tsuki :: Nick :: Parse() {
  int i = 0;
  if(empty() == false) {
    if(static_cast<bool>(std::isalpha(_data[0])) == false &&
      (_data[0] != static_cast<char>(95) && _data[1] != static_cast<char>(95)) &&
       _data[0] != '+' && _data[0] != '@' && _data[0] != '[' && _data[0] != ']' &&
       _data[0] != static_cast<char>(39) && _data[0] != '{' && _data[0] != '}' && _data[0] != '<' &&
       _data[0] != '>' && _data[0] != '^' && _data[0] != '&' && _data[0] != '*' && _data[0] != '$'
       && _data[0] != static_cast<char>(96) && _data[0] != '|' && _data[0] != '\\' && _data[0] != '/' ) { 
       std::string temp = temp + "constants.cpp : In Tsuki::Nick::Parse : " +
                       "First character of a nick can't be non-alpha.\n";
       throw std::runtime_error(temp);
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
        std::string temp = "constants.cpp : In Tsuki::Nick::Parse() : Can't have '" +
                        std::string{_data.at(i)} +"' in Nick.\n";
        throw  std::runtime_error(temp);
      }
    }
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

void Tsuki :: Channel :: clear() {
  _data.clear();
  chan_users.clear();
}

void Tsuki :: Channel  :: Parse() {
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

void Tsuki :: User :: operator= (const User& obj) {
  _data = std::move(obj._data);
  Parse();
}

void Tsuki :: User :: setData(const std::string& data) {
  _data = data;
  Parse();
}

std::string Tsuki :: User :: getData() const { 
  return _data; 
}

void Tsuki :: User :: clear() {
  _data.clear();
}

void Tsuki :: User :: Parse() {
  int i = 0;
  if(empty() == false) {
    for(auto iter = _data.begin(); iter != _data.end(); iter++) {
      i = std::distance(_data.begin(),iter);
      if( (bool) std::isalpha(_data[i]) || (bool) std::isdigit(_data[i]) )
        continue;
      else if(_data[i] == Tsuki::Dash || _data[i] == Tsuki::LeftSquareBrackets ||
        _data[i] == Tsuki::RightSquareBrackets || _data[i] == Tsuki::LeftSlash ||
        _data[i] == Tsuki::SingleQuote || _data[i] == Tsuki::Power ||
        _data[i] == Tsuki::LeftCurlyBraces  || _data[i] == Tsuki::RightCurlyBraces)
        continue;
      else {
        std::string temp = "constants.cpp : In Tsuki::User::Parse() : Can't have a '" +
                           std::string{_data.at(i)}+ "' in the User field.\n";
        std::cout<<"Caught error at line 121, data: "<<_data<<std::endl;
        throw std::runtime_error(temp);
      }
    }
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

std::string Tsuki :: Prefix :: getData() const {
  std::string temp;
  if(_is_server == false) {
    temp = _nick.getData() + "!" + _user.getData() + "@" + _hostname;
  }
  else if(_is_server == true) { temp = _hostname; }
  return temp;
}

void Tsuki :: Prefix :: Parse(const std::string& _data) {
  try {
    std::string temp = _data;
    
    if(_data.find_last_of("net",_data.size()-3) != std::string::npos &&
       _data.find_first_of('!',0) == std::string::npos) {
	  _hostname = _data;
	  _nick.setData("");
      _user.setData("");
      _is_server = true;
	  _is_client = false;
    }
    if(_data.find_first_of('!',0) != std::string::npos && has_alnum(_data) &&
      (_data.find_last_of("net",_data.size()-3) == std::string::npos)) {
	  _is_client = true;
	  _is_server = false;
	  std::string nick = temp.substr(0,temp.find('!'));
      _nick.setData(nick); 
      temp = temp.substr(temp.find('!'));
      std::string user = temp.substr(0,temp.find('@'));
      _user.setData(user); 
      temp = temp.substr(temp.find('@'));
      _hostname = temp;
    }
  }
  catch(std::exception& e) { 
    std::cout<<"Caught exception : \n"<<e.what();
    clear();   
  }
}

bool Tsuki :: has_alnum(const std::string& data)
{
  bool has_it = false,once = true;
  for(auto&& i = std::begin(data); i !=std::end(data); i++) {
    if(std::isalnum(*i)) { has_it = true; }
    else if(!std::isalnum(*i)) { once = false; }
  }
  if((has_it && once) || (!has_it && once)) { has_it = false; }
  return has_it;
}

bool Tsuki :: has_only_spec(const std::string& data)
{
  std::vector<bool> values(data.size());
  bool has_it;
  for(size_t i = 0;i<data.size();i++) {
    if(data[i] == '+' || data[i] == '-' || data[i] == '_' || data[i] == '=' || data[i] == '^' ||
       data[i] == '*' || data[i] == '&' || data[i] == '(' || data[i] == ')' || data[i] == '%' ||
       data[i] == '$' || data[   i] == '#' || data[i] == '@' || data[i] == '!' || data[i] == '{' ||
       data[i] == '[' || data[i] == '}' || data[i] == ']' || data[i] == '\\'|| data[i] == '|'||
       data[i] == ':' || data[i] == ';' || data[i] == '"' || data[i] == '<' || data[i] == '>' ||
       data[i] == '.' || data[i] == '?' || data[i] == '/') {
      values[i] = false;
    }
    else { values[i] = true; }
  }
  for(auto&& i = std::begin(values); i != std::end(values); i++) {
    if(*i == false) { has_it = true; }
  }
  values.clear();
  return has_it;
}

bool Tsuki :: has_only_space(const std::string& data)
{
  std::vector<bool> values(data.size());
  bool has_it = false;
  for(size_t i = 0;i<data.size(); i++) {
    if(data[i] == Tsuki::Space) { values[i] = false; }

    else if(static_cast<bool>(std::isalpha(data[i])) == true || data[i] == static_cast<char>(95) ||
    data[i] == static_cast<char>(95) || data[i] == static_cast<char>(39) || data[i] == static_cast<char>(96) ||
    data[i] == '+' || data[i] == '@' || data[i] == ':' || data[i] == '[' || data[i] == ']' ||
    data[i] == '{' || data[i] == '}' || data[i] == '<' || data[i] == '_' || data[i] == '-' ||
    data[i] == '>' || data[i] == '^' || data[i] == '&' || data[i] == '*' || data[i] == '$' ||
    data[i] == '|' || data[i] == '\\' || data[i] == '/' )
    { values[i] = true; }
    else { values[i] = true; }
  }
  for(auto&& i = std::begin(values); i != std::end(values); i++) {
    if(*i == false) { has_it = true; }
    else { has_it = false; }
  }
  values.clear();
  return has_it;
}

bool Tsuki :: begins_with(const std::string& message,const char* command)
{
  bool value = false; std::string temp1;
  temp1.assign(command);
  if(message.find(temp1) == 0) {
    std::string temp2 = message.substr(0,temp1.size());
    if(temp2.compare(command)==0) { value = true; }
    else { value = false; }
  }
  return value;
}

bool Tsuki :: has_it(const std::string& data,const char* command)
{
  std::vector<std::string> v;  bool ret = false;
  std::string comm{command};
  std::istringstream s(data);
  std::copy(std::istream_iterator<std::string>(s),
	    std::istream_iterator<std::string>(),
	    std::back_inserter(v));
  for(auto i: v) {
    if(i == comm) ret = true;
  }
  v.clear();
  return ret;
}
bool Tsuki :: has_it(const std::string& data,const char& command)
{
  std::vector<std::string> v;  bool ret = false;
  std::string comm{command};
  std::istringstream s(data);
  std::copy(std::istream_iterator<std::string>(s),
	    std::istream_iterator<std::string>(),
	    std::back_inserter(v));
  for(auto i: v) {
    if(i == comm)
    ret = true;
  }
  return ret;
}
