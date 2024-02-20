#include <bits/stdc++.h>

char s[10] = "abc";

int main(){
  std::fstream file;
  file.open("t.txt", std::ios::out | std::ios::binary);
  file.write(reinterpret_cast<char *>(&s), 3 * sizeof(char));
  file.close();
  return 0;
}