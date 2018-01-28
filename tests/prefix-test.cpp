#include <iostream>
#include <string>
#include "../TsukiBot/include/constants.hpp"

using namespace Tsuki;

int main() {
  std::string s1("niven.freenode.net"),s2("weber.freenode.net");
  Prefix p1, p2;
  p1.setData(s1,Type::normal,true);
  p2.setData(s2,Type::normal,true);
  std::cout<<"Prefix 1: \n"
           <<"Hostname: "<<p1.getHostname()<<std::endl
           <<"Nick: "<<p1.getNickData()<<std::endl
           <<"User: "<<p1.getUser().getData()<<std::endl
           <<"Prefix 2: \n"
           <<"Hostname: "<<p2.getHostname()<<std::endl
           <<"Nick: "<<p2.getNick().getData()<<std::endl
           <<"User: "<<p2.getUser().getData()<<std::endl;
  return 0;
}
