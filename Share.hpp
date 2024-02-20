#ifndef include_bits
#include <bits/stdc++.h>
#define include_bits
#endif

const int max_len = 30;
const std::string INT_MAX_ = "2147483647";

int trade_count = 0;

double f[100005], g[100005];

struct interval{
  int l, r;
  inline int len(){return r - l + 1;}
  interval(int L, int R){l = L; r = R;}
  interval(){}
  friend bool operator==(const interval &a, const interval &b){
    return a.l == b.l && a.r == b.r;
  }
  friend bool operator!=(const interval &a, const interval &b){
    return !(a == b);
  }
};

class account;

bool operator==(const char *a, const std::string &b){
  if(strlen(a) ^ b.size()) return false;
  int temp_len = strlen(a);
  for(int i = 0; i < temp_len; ++i) if(a[i] ^ b[i]) return false;
  return true;
}

bool operator==(const std::string &a, const char *b){
  return b == a;
}
bool operator!=(const char *a, const std::string &b){
  return !(a == b);
}

bool operator!=(const std::string &a, const char *b){
  return !(a == b);
}

bool operator<=(const std::string &a, const char *b){
  int la = a.size(), lb = strlen(b);
  for(int i = 0; i < std::min(la, lb); ++i) if(a[i] < b[i]) return true; else if(a[i] > b[i]) return false;
  if(la <= lb) return true;
  else return false;
}

bool operator<=(const char *a, const std::string &b){
  int la = strlen(a), lb = b.size();
  for(int i = 0; i < std::min(la, lb); ++i) if(a[i] < b[i]) return true; else if(a[i] > b[i]) return false;
  if(la <= lb) return true;
  else return false;
}

bool operator>=(const std::string &a, const char *b){
  return b <= a;
}

bool operator>=(const char *a, const std::string &b){
  return b <= a;
}

bool leq(const char *a, const char *b){
  int la = strlen(a), lb = strlen(b);
  for(int i = 0; i < std::min(la, lb); ++i) if(a[i] < b[i]) return true; else if(a[i] > b[i]) return false;
  if(la <= lb) return true;
  else return false;
}

bool eq(const char *a, const char *b){
  int la = strlen(a), lb = strlen(b);
  if(la ^ lb) return false;
  for(int i = 0; i < la; ++i) if(a[i] ^ b[i]) return false;
  return true;
}

bool geq(const char *a, const char *b){
  return leq(b, a);
}

void Give(char *a, std::string &b){
  for(int i = 0; i < b.size(); ++i) a[i] = b[i];
  return ;
}

inline void fail(){
  printf("Invalid\n");
  return ;
}