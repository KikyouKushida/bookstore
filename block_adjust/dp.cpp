#include <bits/stdc++.h>

std::set <int> s[26];

int n;

int main(){
  freopen("in.txt", "r", stdin);
  freopen("ans.txt", "w", stdout);
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i){
    std::string type, str; int val;
    std::cin >> type >> str;
    if(type == "insert"){
      std::cin >> val;
      if(s[str[0] - 'a'].find(val) != s[str[0] - 'a'].end()){
        printf("WA %d\n", i);
        assert(0);
      }
      s[str[0] - 'a'].insert(val);
    }
    else if(type == "delete"){
      std::cin >> val;
      if(s[str[0] - 'a'].find(val) != s[str[0] - 'a'].end()){
        s[str[0] - 'a'].erase(val);
      }
    }
    else {
      auto it = s[str[0] - 'a'].begin();
      while(it != s[str[0] - 'a'].end()){
        printf("%d", *it);
        ++it;
        if(it != s[str[0] - 'a'].end()) printf(" ");
      }
      if(s[str[0] - 'a'].size() == 0) printf("null");
      printf("\n");
    }
  }
  return 0;
}
