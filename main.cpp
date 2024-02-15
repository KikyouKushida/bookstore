#ifndef inclu
#include <bits/stdc++.h>
#define inclu
#endif

#include "Share.hpp"
#include "AccountSystem.hpp"

void Deal(std::string &read_in, std::vector <interval> &info){
  if(read_in.size() == 0) return ;
  info.clear();
  std::string tmp; int len = read_in.size();
  while(len >= 1 && read_in[len - 1] == ' ') --len;
  for(int i = 0; i < len; ++i) tmp += read_in[i];
  std::reverse(tmp.begin(), tmp.end());
  read_in.clear();
  len = tmp.size();
  while(len >= 1 && tmp[len - 1] == ' ') --len;
  for(int i = 0; i < len; ++i) read_in += tmp[i];
  std::reverse(read_in.begin(), read_in.end());
  for(int i = 0, j; i < read_in.size(); i = j + 1){
    j = i;
    if(read_in[j] == ' ') continue;
    while(j + 1 < read_in.size() && read_in[j + 1] != ' ') ++j;
    info.push_back(interval(i, j));
  }
  return ;
}

void Initialize(){
  account now("root", "sjtu", "root", 7);
  block::Initialize();
  block::Insert(now);
  return ;
}

int main(){
  std::string read_in;
  std::vector <interval> info;
  Initialize();
  while(true){
    getline(std::cin, read_in);
    Deal(read_in, info);
    if(read_in.size() == 0) continue;
    assert(info.size() >= 1);
    if(info[0] == interval(0, 1) && read_in.substr(0, 2) == "su") LogIn_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "logout") LogOut_account();
    else if(info[0] == interval(0, 7) && read_in.substr(0, 8) == "register") Register_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "passwd") Change_pass_word(read_in, info);
    else if(info[0] == interval(0, 6) && read_in.substr(0, 7) == "useradd") Create_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "delete") Delete_account(read_in, info);
    else if(read_in == "exit" || read_in == "quit") break;
    printf("current_privilege = %d\n", current_privilege);
  }
  block::Store();
  return 0;
}