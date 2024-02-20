#ifndef include_bits
#include "share.hpp"
#define include_bits
#endif
class account{
public:
  int privilege, count, select;
  char user_id[32], pass_word[32], user_name[32];
  account(){
    count = privilege = select = 0; 
    for(int i = 0; i < max_len + 1; ++i) user_id[i] = pass_word[i] = user_name[i] = 0;
  }
  account(const std::string &a, const std::string &b, const std::string &c, const int &d, const int &e = 0){
    for(int i = 0; i < max_len + 1; ++i) user_id[i] = pass_word[i] = user_name[i] = 0;
    for(int i = 0; i < a.size(); ++i) user_id[i] = a[i];
    for(int i = 0; i < b.size(); ++i) pass_word[i] = b[i];
    for(int i = 0; i < c.size(); ++i) user_name[i] = c[i];
    privilege = d;
    count = 0;
    select = e;
  }
  account& operator=(const account &rhs){
    privilege = rhs.privilege;
    count = rhs.count;
    select = rhs.select;
    for(int i = 0; i < max_len; ++i){
      user_id[i] = rhs.user_id[i];
      pass_word[i] = rhs.pass_word[i];
      user_name[i] = rhs.user_name[i];
    }
    return *this;
  }
  friend bool operator==(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i) if(a.user_id[i] ^ b.user_id[i]) return false;
    return true; 
  }
  friend bool operator<(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i)
      if(a.user_id[i] < b.user_id[i]) return true;
      else if(a.user_id[i] > b.user_id[i]) return false;
    return false; 
  }
  friend bool operator<=(const account &a, const account &b){
    for(int i = 0; i < max_len; ++i)
      if(a.user_id[i] < b.user_id[i]) return true;
      else if(a.user_id[i] > b.user_id[i]) return false;
    return true; 
  }
  friend bool operator>(const account &a, const account &b){
    return b < a;
  }
  friend bool operator>=(const account &a, const account &b){
    return b <= a;
  }
  void simple_write(std::fstream &File){
    File.write(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.write(reinterpret_cast<char *>(&count), sizeof(int));
    File.write(reinterpret_cast<char *>(&select), sizeof(int));
    return ;
  }
  void write(std::fstream &File, const std::string &file_name, const int &index){
    File.open(file_name, std::ios::out | std::ios::binary);
    File.seekp(index * sizeof(char), std::ios::beg);
    File.write(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.write(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.write(reinterpret_cast<char *>(&count), sizeof(int));
    File.write(reinterpret_cast<char *>(&select), sizeof(int));
    File.close();
    return ;
  }
  void read(std::fstream &File, const std::string &file_name, const int &index){
    File.open(file_name, std::ios::in | std::ios::binary);
    File.seekg(index * sizeof(char), std::ios::beg);
    File.read(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.read(reinterpret_cast<char *>(&count), sizeof(int));
    File.read(reinterpret_cast<char *>(&select), sizeof(int));
    File.close();
    return ;
  }
  void simple_read(std::fstream &File){
    File.read(reinterpret_cast<char *>(&user_id), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&pass_word), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&user_name), max_len * sizeof(char));
    File.read(reinterpret_cast<char *>(&privilege), sizeof(int));
    File.read(reinterpret_cast<char *>(&count), sizeof(int));
    File.read(reinterpret_cast<char *>(&select), sizeof(int));
    return ;
  }
};

namespace block{

const int B = 300, L = 3 * max_len + 12;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data.txt", list_data_name = "list_data.txt", head_data_name = "head_data.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

account Head_data[1005], temp[1005];

void Insert(const account &cur);

void Delete_any(const int &p, const int &q){
  if(siz[p] == 1){
    for(int i = p; i <= cnt - 1; ++i) Head_data[i] = Head_data[i + 1];
    cnt -= 1;
    return ;
  }
  user_data.seekg((head[p] + q * L) * sizeof(char), std::ios::beg);
  for(int i = q + 1; i <= siz[p]; ++i) temp[i].simple_read(user_data);
  user_data.seekp((head[p] + (q - 1) * L) * sizeof(char), std::ios::beg);
  for(int i = q + 1; i <= siz[p]; ++i) temp[i].simple_write(user_data);
  siz[p] -= 1;
  user_data.seekg(head[p] * sizeof(char), std::ios::beg);
  Head_data[p].simple_read(user_data);
  return ;
}

void Initialize(){
  std::ifstream ifile;
  ifile.open(user_data_name);
  if(!ifile){
    user_data.open(user_data_name, std::ios::out | std::ios::binary);
    user_data.close();
    account ST;
    ST.write(user_data, user_data_name, 0);
    head[cnt = 1] = 0, siz[1] = 1, nownew = L * B;
    head_data.open(head_data_name, std::ios::out | std::ios::binary);
    head_data.close();
  }
  else {
    ifile.close();
    list_data.open(list_data_name, std::ios::in | std::ios::out | std::ios::binary);
    list_data.seekg(0, std::ios::beg);
    list_data.read(reinterpret_cast<char *>(&cnt), sizeof(int));
    list_data.read(reinterpret_cast<char *>(&nownew), sizeof(int));
    for(int i = 1; i <= cnt; ++i){
      list_data.read(reinterpret_cast<char *>(&head[i]), sizeof(int));
      list_data.read(reinterpret_cast<char *>(&siz[i]), sizeof(int));
    }
    list_data.close();
    user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
    for(int i = 1; i <= cnt; ++i){
      user_data.seekp(head[i] * sizeof(char), std::ios::beg);
      Head_data[i].simple_read(user_data);
    }
    user_data.close();
  }
  account now("root", "sjtu", "root", 7);
  Insert(now);
  return ;
}

void Store(){
  list_data.open(list_data_name, std::ios::out | std::ios::binary);
  list_data.seekp(0, std::ios::beg);
  list_data.write(reinterpret_cast<char *>(&cnt), sizeof(int));
  list_data.write(reinterpret_cast<char *>(&nownew), sizeof(int));
  for(int i = 1; i <= cnt; ++i){
    list_data.write(reinterpret_cast<char *>(&head[i]), sizeof(int));
    list_data.write(reinterpret_cast<char *>(&siz[i]), sizeof(int));
  }
  list_data.close();
  return ;
}

void Insert(const account &cur){
  //printf("To insert: ");
  //std::cout << cur.user_id << "\n";
  int choose = -1;
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i] <= cur) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    temp[i].simple_read(user_data);
    if(temp[i] <= cur) put = i;
  }
  for(int i = size; i >= put + 1; --i) temp[i + 1] = temp[i];
  temp[put + 1] = cur; siz[choose] += 1; size += 1;
  if(put == 0) Head_data[choose] = cur;
  if(siz[choose] <= B){
    user_data.seekp(head[choose] * sizeof(char), std::ios::beg);
    for(int i = 1; i <= size; ++i) temp[i].simple_write(user_data);
  }
  else {
    siz[choose] >>= 1; siz[++cnt] = size - siz[choose];
    head[cnt] = nownew; nownew += L * B;
    user_data.seekp(head[choose] * sizeof(char), std::ios::beg);
    for(int i = 1; i <= siz[choose]; ++i) temp[i].simple_write(user_data);
    user_data.seekp(head[cnt] * sizeof(char), std::ios::beg);
    Head_data[cnt] = temp[siz[choose] + 1];
    for(int i = 1; i <= siz[cnt]; ++i) temp[siz[choose] + i].simple_write(user_data);
    for(int i = cnt - 1; i >= choose + 1; --i){
      std::swap(head[i], head[i + 1]), std::swap(siz[i], siz[i + 1]); 
      std::swap(Head_data[i], Head_data[i + 1]);
    }
  }
  user_data.close();
  return ;
}

void get_info(const std::string &user_id, account &now){
  int start = 0, hav = 0;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].user_id <= user_id) start = i;
    else break;
  assert(start != 0);
  account tmp;
  for(int i = start; i <= start; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      //std::cout << "get_info user_data = ? " << strlen(tmp.user_id) << "\n";
      if(tmp.user_id == user_id){
        now = tmp;
        user_data.close();
        return ;
      }
      if(tmp.user_id > user_id) break;
    }
  }
  tmp.privilege = -1;
  now = tmp;
  user_data.close();
  return ;
}

void Delete(const std::string &user_id){
  int choose = -1; account tmp;
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].user_id <= user_id) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= siz[choose]; ++i){
    tmp.simple_read(user_data);
    if(tmp.user_id == user_id){
      Delete_any(choose, i);
      break;
    }
  }
  user_data.close();
  return ;
}

void Update_pass_word(const std::string &user_id, const std::string &new_pass_word){
  int start = 0, hav = 0;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].user_id <= user_id) start = i;
    else break;
  assert(start != 0);
  account tmp;
  char S[32];
  for(int i = 0; i < new_pass_word.size(); ++i) S[i] = new_pass_word[i];
  for(int i = new_pass_word.size(); i < max_len; ++i) S[i] = 0;
  for(int i = start; i <= start; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(tmp.user_id == user_id){
        user_data.seekp(head[i] * sizeof(char) + (j - 1) * L + max_len);
        user_data.write(reinterpret_cast<char *>(&S), max_len * sizeof(char));
        user_data.close();
        return ;
      }
      if(tmp.user_id > user_id) break;
    }
  }
  user_data.close();
  return ;
}

}

bool check_user_id_or_pass_word(const std::string &a){
  if(a.size() > max_len) return false;
  for(int i = 0; i < a.size(); ++i) 
    if(a[i] != '_' && !(a[i] >= '0' && a[i] <= '9')
    && !(a[i] >= 'a' && a[i] <= 'z') && !(a[i] >= 'A' && a[i] <= 'Z'))
      return false;
  return true;
}

bool check_user_name(const std::string &user_name){
  if(user_name.size() > max_len) return false;
  for(int i = 0; i < user_name.size(); ++i) 
    if(user_name[i] == 127 || (user_name[i] >= 0 && user_name[i] <= 32))
      return false;
  return true;
}

bool check_privilege(const std::string &privilege){
  if(privilege.size() != 1) return false;
  if(privilege[0] != '7' && privilege[0] != '3' && privilege[0] != '1') return false;
  return true;
}

std::vector <account> log_in;
int current_privilege = 0;

inline void update_current_privilege(){
  if(log_in.size() == 0) current_privilege = 0;
  else current_privilege = log_in[log_in.size() - 1].privilege;
  return ;
}

void LogIn_account(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() <= 1 || info.size() >= 4){
    fail();
    return ;
  } // fail in form
  assert(info.size());
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  //std::cout << "user_id = " << user_id << "\n";
  //printf("y1\n");
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  //printf("y2\n");
  if(now.privilege == -1){
    fail();
    //printf("fail on privilege == -1\n");
    return ;
  } 
  if(info.size() == 3){
    std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1);
    if(pass_word != now.pass_word){
      fail();
      //printf("y3\n");
      return ;
    }
    else {
      log_in.push_back(now);
      update_current_privilege();
      //printf("y4\n");
      return ;
    }
  }
  if(current_privilege > now.privilege){
    log_in.push_back(now);
    update_current_privilege();
    return ;
  }
  else {
    fail();
    return ;
  }
}

void LogOut_account(){
  if(log_in.size() == 0){
    fail();
    return ;
  }
  log_in.pop_back();
  update_current_privilege();
  return ;
} 

void Register_account(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 4){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege != -1){
    fail();
    return ;
  }
  //printf("out 1\n");
  std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1), 
              user_name = read_in.substr(info[3].l, info[3].r - info[3].l + 1);
  if(!check_user_id_or_pass_word(pass_word)){
    fail();
    return ;
  }
  if(!check_user_name(user_name)){
    fail();
    return ;
  }
  //printf("out 2\n");
  account tmp(user_id, pass_word, user_name, 1);
  block::Insert(tmp);
  //printf("out 3\n");
  return ;
}

void Create_account(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 5 || current_privilege < 3){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  //std::cout << "To create user_id = " << user_id << "\n";
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  } 
  account now; 
  block::get_info(user_id, now);
  if(now.privilege != -1){
    fail();
    return ;
  }
  std::string pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1), 
              user_name = read_in.substr(info[4].l, info[4].r - info[4].l + 1);
  if(!check_user_id_or_pass_word(pass_word)){
    fail();
    return ;
  } 
  if(!check_user_name(user_name)){
    fail();
    return ;
  }
  if(!check_privilege(read_in.substr(info[3].l, info[3].r - info[3].l + 1))){
    fail();
    return ;
  }
  int privilege = read_in[info[3].l] - '0';
  if(privilege >= current_privilege){
    fail();
    return ;
  }
  account tmp(user_id, pass_word, user_name, privilege);
  block::Insert(tmp);
  return ;
}

void Change_pass_word(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() < 3 || info.size() > 4 || current_privilege < 1){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege == -1){
    fail();
    return ;
  }
  if(info.size() == 3){
    if(current_privilege != 7){
      fail();
      return ;
    }
    std::string new_pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1);
    if(!check_user_id_or_pass_word(new_pass_word)){
      fail();
      return ;
    }
    block::Update_pass_word(user_id, new_pass_word);
    return ;
  }
  std::string previous_pass_word = read_in.substr(info[2].l, info[2].r - info[2].l + 1),
              new_pass_word = read_in.substr(info[3].l, info[3].r - info[3].l + 1);
  if(!check_user_id_or_pass_word(previous_pass_word)){
    fail();
    return ;
  }
  if(!check_user_id_or_pass_word(new_pass_word)){
    fail();
    return ;
  }
  if(previous_pass_word != now.pass_word){
    fail();
    return ;
  }
  block::Update_pass_word(user_id, new_pass_word);
  return ;
}

void Delete_account(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 2 || current_privilege < 7){
    fail();
    return ;
  }
  std::string user_id = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_user_id_or_pass_word(user_id)){
    fail();
    return ;
  }
  account now; 
  block::get_info(user_id, now);
  if(now.privilege == -1 || now.count > 0){
    fail();
    return ;
  }
  block::Delete(user_id);
  return ;
}