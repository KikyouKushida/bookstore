#include <bits/stdc++.h>

int main(){
  // std::ofstream out("a.txt", std::ofstream::binary);
  // int i;
  // if(!out) {std::cout << "fik\n"; return 0;}
  // for(int i = 1; i <= 10; ++i) out.write(reinterpret_cast<char *>(&i), sizeof(int));
  // out.close();

  // std::ifstream in("a.txt", std::ifstream::binary);
  // if(!in) {std::cout << "fik\n"; return 0;}
  // in.read(reinterpret_cast<char *>(&i), sizeof(int));
  // while(!in.eof()){
  //   std::cout << i << "\n";
  //   in.read(reinterpret_cast<char *>(&i), sizeof(int));
  // }
  std::fstream f("a.txt", std::ios::out | std::ios::binary);
  f.seekg(0);
  printf("%d\n", (int)f.tellg());
  return 0;
}