#ifndef include_bits
#include "share.hpp"
#define include_bits
#endif

int Get_num(const std::string &a){
  if(a.size() < 1 || a.size() > 10) return -1;
  for(int i = 0; i < a.size(); ++i) if(!isdigit(a[i])) return -1;
  if(a.size() == 10){
    for(int i = 0; i < 10; ++i) 
      if(a[i] < INT_MAX_[i]) break;
      else if(a[i] > INT_MAX_[i]) return -1;
  }
  int res = 0;
  for(int i = 0; i < a.size(); ++i) res *= 10, res += a[i] - '0';
  return res;
} 

void Show_finance(std::string &read_in, std::vector <interval> &info){
  if(info.size() < 2 || info.size() > 3){
    fail();
    return ;
  }
  if(info[1] != interval(5, 11) || read_in.substr(5, 7) != "finance"){
    fail();
    return ;
  }
  if(info.size() == 2) printf("+ %.2lf - %.2lf\n", f[trade_count], g[trade_count]);
  else {
    int num = Get_num(read_in.substr(info[2].l, info[2].r - info[2].l + 1));
    if(num == -1){
      fail();
      return ;
    }
    else if(num > trade_count) fail();
    else if(num == 0) printf("\n");
    else printf("+ %.2lf - %.2lf\n", f[trade_count] - f[trade_count - num], g[trade_count] - g[trade_count - num]);
  }
  return ;
}

void Report_finance(){
  printf("---------------------------------------------------\n\n");
  if(trade_count == 0) printf("You have not completed any bargains.\n");
  else {
    printf("You have already completed %d bargains.\n", trade_count);
    printf("You have already earned %.2lf dollars and spended %.2lf dollars.\n", f[trade_count], g[trade_count]);
  }
  printf("\n---------------------------------------------------\n");
  return ;
}

void Report_employee(){
  printf("---------------------------------------------------\n\n");

  printf("\n---------------------------------------------------\n");
  return ;
}

void Log(){
  printf("---------------------------------------------------\n\n");
  
  printf("\n---------------------------------------------------\n");
  return ;
}