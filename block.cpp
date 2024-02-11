#include <bits/stdc++.h>

const int B = 500, L = 17;
char space = ' ';
std::fstream file, leif, Head;
std::ifstream ifile;
std::string file_name = "f.txt", leif_name = "g.txt", Head_name = "h.txt";

struct par{
  std::string s;
  int val;
  par(){s = ""; val = 0;}
  par(std::string rs, int rval){
    s = rs;
    val = rval;
  }
  friend bool operator < (par &a, par &b){
    return a.s != b.s ? a.s < b.s : a.val < b.val;
  }
  friend bool operator == (par &a, par &b){
    return a.s == b.s && a.val == b.val;
  }
  void write(int index){
    file.open(file_name, std::ios::out | std::ios::binary);
    file.seekp(index * sizeof(int));
    for(int i = 0; i < 64; ++i) 
      if(i < s.size()) file.write(reinterpret_cast<char *>(&s[i]), sizeof(char));
      else file.write(reinterpret_cast<char *>(&space), sizeof(char));
    file.write(reinterpret_cast<char *>(&val), sizeof(int));
    file.close();
    return ;
  }
  void simple_write(){
    for(int i = 0; i < 64; ++i) 
      if(i < s.size()) file.write(reinterpret_cast<char *>(&s[i]), sizeof(char));
      else file.write(reinterpret_cast<char *>(&space), sizeof(char));
    file.write(reinterpret_cast<char *>(&val), sizeof(int));
    return ;
  }
  par& operator=(const par &other){
    val = other.val;
    s = other.s;
    return *this;
  }
}temp[B + 5];

void read(int index, par &x){
  file.open(file_name, std::ios::in | std::ios::binary);
  file.seekg(index * sizeof(int), std::ios::beg);
  char c; x.s = "";
  for(int i = 0; i < 64; ++i){
    file.read(reinterpret_cast<char *>(&c), sizeof(char));
    if(c != ' ') x.s += c;
  }
  file.read(reinterpret_cast<char *>(&(x.val)), sizeof(int));
  file.close();
  return ;
}

void simple_read(std::string &tmp){
  char c; tmp.clear();
  for(int i = 0; i < 64; ++i){
    file.read(reinterpret_cast<char *>(&c), sizeof(char));
    if(c != ' ') tmp += c;
  }
  return ;
}

void simple_read(int &tmp){
  tmp = 0;
  file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
  return ;
}

int head[100005], cnt = 0, siz[100005], nownew = 0;

void delete_any(int p, int q){
  if(siz[p] == 1){
    for(int i = p; i <= cnt - 1; ++i) siz[i] = siz[i + 1], head[i] = head[i + 1];
    cnt -= 1;
    return ;
  }
  file.seekg((head[p] + q * L) * sizeof(int), std::ios::beg);
  for(int i = q + 1; i <= siz[p]; ++i) simple_read(temp[i].s), simple_read(temp[i].val);
  file.seekp((head[p] + (q - 1) * L) * sizeof(int), std::ios::beg);
  for(int i = q + 1; i <= siz[p]; ++i) temp[i].simple_write();
  siz[p] -= 1;
  return ;
}

void initialize(){
  ifile.open(file_name);
  if(!ifile){
    file.open(file_name, std::ios::out | std::ios::binary);
    file.close();
    par ST("", 0);
    ST.write(0);
    head[cnt = 1] = 0, siz[1] = 1;
    nownew = L * B;
  }
  else {
    ifile.close();
    leif.open(leif_name, std::ios::in | std::ios::out | std::ios::binary);
    leif.seekg(0, std::ios::beg);
    leif.read(reinterpret_cast<char *>(&cnt), sizeof(int));
    leif.read(reinterpret_cast<char *>(&nownew), sizeof(int));
    for(int i = 1; i <= cnt; ++i){
      leif.read(reinterpret_cast<char *>(&head[i]), sizeof(int));
      leif.read(reinterpret_cast<char *>(&siz[i]), sizeof(int));
    }
    leif.close();
  }
  return ;
}

void store(){
  leif.open(leif_name, std::ios::out | std::ios::binary);
  leif.seekp(0, std::ios::beg);
  leif.write(reinterpret_cast<char *>(&cnt), sizeof(int));
  leif.write(reinterpret_cast<char *>(&nownew), sizeof(int));
  for(int i = 1; i <= cnt; ++i){
    leif.write(reinterpret_cast<char *>(&head[i]), sizeof(int));
    leif.write(reinterpret_cast<char *>(&siz[i]), sizeof(int));
  }
  leif.close();
  return ;
}

void insert(std::string str, int value){
  int tmpv; std::string tmps;
  par cur(str, value);
  int choose = -1;
  for(int j = 1; j <= cnt; ++j){
    par now; read(head[j], now);
    if(now == cur){
      choose = -1;
      break;
    }
    else if(now < cur) choose = j;
    else break;
  }
  if(choose == -1) return ;
  file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; file.seekg(head[choose] * sizeof(int), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    char c; temp[i].s = "";
    for(int j = 0; j < 64; ++j){
      file.read(reinterpret_cast<char *>(&c), sizeof(char));
      if(c != ' ') temp[i].s += c;
    }
    file.read(reinterpret_cast<char *>(&(temp[i].val)), sizeof(int));
    if(temp[i] == cur) put = -1;
    else if(temp[i] < cur) put = i;
  }
  if(put == -1){
    file.close();
    return ;
  } 
  for(int i = size; i >= put + 1; --i) temp[i + 1] = temp[i];
  temp[put + 1] = cur; siz[choose] += 1; size += 1;
  if(siz[choose] <= B){
    file.seekp(head[choose] * sizeof(int), std::ios::beg);
    for(int i = 1; i <= size; ++i) temp[i].simple_write();
  }
  else {
    siz[choose] >>= 1; siz[++cnt] = size - siz[choose];
    head[cnt] = nownew; nownew += L * B;
    file.seekp(head[choose] * sizeof(int), std::ios::beg);
    for(int i = 1; i <= siz[choose]; ++i) temp[i].simple_write();
    file.seekp(head[cnt] * sizeof(int), std::ios::beg);
    for(int i = 1; i <= siz[cnt]; ++i) temp[siz[choose] + i].simple_write();
    for(int i = cnt - 1; i >= choose + 1; --i) std::swap(head[i], head[i + 1]), std::swap(siz[i], siz[i + 1]); 
  }
  file.close();
  return ;
}

void find(std::string str){
  int status = 0, start = 0, hav = 0, tmpv;
  std::string tmps;
  file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  for(int i = 1; i <= cnt; ++i){
    file.seekg(head[i] * sizeof(int), std::ios::beg);
    simple_read(tmps);
    if(tmps < str) start = i;
    else break;
  }
  assert(start != 0);
  for(int i = start; i <= cnt; ++i){
    if(status == 2) break;
    file.seekg(head[i] * sizeof(int), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      simple_read(tmps);
      simple_read(tmpv);
      if(tmps == str){
        hav = 1;
        if(status == 0) std::cout << tmpv, status = 1;
        else std::cout << " " << tmpv;
      }
      if(tmps > str){
        status = 2;
        break;
      }
    }
  }
  if(hav == 0) std::cout << "null" << "\n";
  else std::cout << "\n";
  file.close();
  return ;
}

void erase(std::string str, int value){
  std::string tmps; int tmpv;
  par cur(str, value);         
  int choose = -1;
  for(int j = 1; j <= cnt; ++j){
    par now; read(head[j], now);
    if(now == cur){
      choose = -1;
      file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
      delete_any(j, 1);
      file.close();
      break;
    }
    else if(now < cur) choose = j;
  }
  if(choose == -1) return ;
  file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
  file.seekg(head[choose] * sizeof(int), std::ios::beg);
  for(int i = 1; i <= siz[choose]; ++i){
    simple_read(tmps);
    simple_read(tmpv);
    if(tmps == str && tmpv == value){
      delete_any(choose, i);
      break;
    }
  }
  file.close();
  return ;
}

int main(){
  initialize();
  //std::ios::sync_with_stdio(false);
  //std::cin.tie(0), std::cout.tie(0);
  int n; std::cin >> n;
  for(int T = 1; T <= n; ++T){
    std::string type, str, tmps; 
    std::cin >> type >> str;
    int value, tmpv;
    if(type == "find") find(str);
    else if(type == "insert"){
      std::cin >> value;
      insert(str, value);
    }
    else {
      std::cin >> value;
      erase(str, value);
    }
  }
  store();
  return 0;
}