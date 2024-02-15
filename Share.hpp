#ifndef inclu
#include <bits/stdc++.h>
#define inclu
#endif

const int max_len = 30;

struct interval{
  int l, r;
  inline int len(){return r - l + 1;}
  interval(int L, int R){l = L; r = R;}
  interval(){}
  friend bool operator==(const interval &a, const interval &b){
    return a.l == b.l && a.r == b.r;
  }
};
class account;

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

// bool operator==(const char *a, const char *b){
//   if(strlen(a) ^ strlen(b)) return false;
//   int temp_len = strlen(a);
//   for(int i = 0; i < temp_len; ++i) if(a[i] ^ b[i]) return false;
//   return true;
// }

bool operator==(const char *a, const std::string &b){
  if(strlen(a) ^ b.size()) return false;
  int temp_len = strlen(a);
  for(int i = 0; i < temp_len; ++i) if(a[i] ^ b[i]) return false;
  return true;
}

bool operator==(const std::string &a, const char *b){
  return b == a;
}

// bool operator!=(const char *a, const char *b){
//   return !(a == b);
// }

bool operator!=(const char *a, const std::string &b){
  return !(a == b);
}

bool operator!=(const std::string &a, const char *b){
  return !(a == b);
}

// bool operator<=(const char *a, const char *b){
//   for(int i = 0; i < max_len; ++i) 
//     if(a[i] < b[i]) return true;
//     else if(a[i] > b[i]) return false;
//   return true;
// }

// bool operator>=(const char *a, const char *b){
//   return b <= a;
// }

bool leq(const char *a, const char *b){
  for(int i = 0; i < max_len; ++i) 
     if(a[i] < b[i]) return true;
     else if(a[i] > b[i]) return false;
  return true;
}

bool geq(const char *a, const char *b){
  return leq(b, a);
}

inline void fail(){
  printf("Invalid\n");
  return ;
}
