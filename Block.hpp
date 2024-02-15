#ifndef inclu
#include <bits/stdc++.h>
#define inclu
#endif

namespace block{

const int B = 300, L = 3 * max_len + 12;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data.txt", list_data_name = "list_data.txt", head_data_name = "head_data.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

account Head_data[1005], temp[1005];

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
    if(temp[i] < cur) put = i;
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