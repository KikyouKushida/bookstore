#include <bits/stdc++.h>

std::set <int> s[26];

int n = 10000;

std::mt19937 rnd(114514);

int main(){
  freopen("in.txt", "w", stdout);
  printf("%d\n", n);
  for(int i = 1; i <= n; ++i){
    int type = rnd() % 3;
    if(type == 0){
      int zm = rnd() % 26;
      printf("insert %c", zm + 'a');
      int val = rnd() % 1000; 
      while(s[zm].find(val) != s[zm].end()) val = rnd() % 1000;
      s[zm].insert(val);
      printf(" %d\n", val);
    }
    else if(type == 1){
      int zm = rnd() % 26;
      printf("delete %c", zm + 'a');
      int val = rnd() % 1000;
      printf(" %d\n", val);
      s[zm].erase(val);
    }
    else {
      int zm = rnd() % 26;
      printf("find %c\n", zm + 'a');
    }
  }
  return 0;
}