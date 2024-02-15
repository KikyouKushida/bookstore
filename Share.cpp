#ifndef inclu
#include <bits/stdc++.h>
#define inclu
#endif

struct interval{
  int l, r;
  inline int len(){return r - l + 1;}
  interval(int L, int R){l = L; r = R;}
  interval(){}
};

void trans(std::string &read_in, std::vector <interval> &info){
  std::vector <interval>().swap(info);
  assert(info.size() == 0);
  for(int i = 0, j; i < read_in.size(); i = j + 1){
    j = i;
    if(read_in[i] == ' ') continue;
    while(j + 1 < read_in.size() && read_in[j + 1] != ' ') ++j;
    info.push_back(interval(i, j));
  }
  return ;
}

bool operator=(char *a, char *b){
  if(strlen(a) ^ strlen(b)) return false;
  int temp_len = strlen(a);
  for(int i = 0; i < temp_len; ++i) if(a[i] ^ b[i]) return false;
  return true;
}