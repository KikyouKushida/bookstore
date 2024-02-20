#ifndef include_bits
#include "share.hpp"
#define include_bits
#endif

namespace by_ISBN{

const int B = 300, L = Book_data_Len;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data_1.txt", list_data_name = "list_data_1.txt", head_data_name = "head_data_1.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

book Head_data[1005], temp[1005];

void Insert(const book &cur);

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
    book ST;
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

void Insert(const book &cur){
  int choose = -1;
  for(int i = 1; i <= cnt; ++i)
    if(leq_1(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    temp[i].simple_read(user_data);
    if(leq_1(temp[i], cur)) put = i;
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

void get_info(const std::string &ISBN, book &now){
  int start = 0, hav = 0;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].ISBN <= ISBN) start = i;
    else break;
  assert(start != 0);
  book tmp;
  for(int i = start; i <= start; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(tmp.ISBN == ISBN){
        now = tmp;
        user_data.close();
        return ;
      }
      if(tmp.ISBN > ISBN) break;
    }
  }
  tmp.id = -1;
  now = tmp;
  user_data.close();
  return ;
}

void Delete(const std::string &ISBN){
  int choose = -1; book tmp;
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].ISBN <= ISBN) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= siz[choose]; ++i){
    tmp.simple_read(user_data);
    if(tmp.ISBN == ISBN){
      Delete_any(choose, i);
      break;
    }
  }
  user_data.close();
  return ;
}

void Show_all(){
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  book tmp; 
  for(int i = 1; i <= cnt; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(i != 1 || j != 1) Show_one(tmp);
    }
  }
  return ;
}

}

namespace by_book_name{

const int B = 300, L = Book_data_Len;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data_2.txt", list_data_name = "list_data_2.txt", head_data_name = "head_data_2.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

book Head_data[1005], temp[1005];

void Insert(const book &cur);

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
    book ST;
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

void Insert(const book &cur){
  int choose = -1;
  for(int i = 1; i <= cnt; ++i)
    if(leq_2(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    temp[i].simple_read(user_data);
    if(leq_2(temp[i], cur)) put = i;
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

void Delete(const book &cur){
  int choose = -1; book tmp;
  for(int i = 1; i <= cnt; ++i)
    if(leq_2(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  int flag = 0;
  for(int i = 1; i <= siz[choose]; ++i){
    tmp.simple_read(user_data);
    //printf("tmp:\n");
    //Show_one(tmp);
    if(tmp.id == cur.id && eq(tmp.book_name, cur.book_name)){
      Delete_any(choose, i);
      flag = 1;
      break;
    } // this is absolutely right!
  }
  //i//f(flag == 0) printf("delete failed.2\n");
  user_data.close();
  return ;
}

void Find(const std::string &book_name, std::vector <int> &ids){
  int choose = -1; 
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].book_name < book_name) choose = i;
    else break;
  assert(choose != -1);
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  int flag = 1; book tmp;
  for(int i = choose; i <= cnt; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(tmp.book_name == book_name) ids.push_back(tmp.id);
      else if(tmp.book_name > book_name){
        flag = 0;
        break;
      }
    }
    if(flag == 0) break;
  }
  user_data.close();
  return ;
}

}

namespace by_author{

const int B = 300, L = Book_data_Len;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data_3.txt", list_data_name = "list_data_3.txt", head_data_name = "head_data_3.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

book Head_data[1005], temp[1005];

void Insert(const book &cur);

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
    book ST;
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

void Insert(const book &cur){
  int choose = -1;
  for(int i = 1; i <= cnt; ++i)
    if(leq_3(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    temp[i].simple_read(user_data);
    if(leq_3(temp[i], cur)) put = i;
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

void Delete(const book &cur){
  int choose = -1; book tmp;
  for(int i = 1; i <= cnt; ++i)
    if(leq_3(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  int flag = 0;
  for(int i = 1; i <= siz[choose]; ++i){
    tmp.simple_read(user_data);
    if(tmp.id == cur.id && eq(tmp.author, cur.author)){
      Delete_any(choose, i);
      flag = 1;
      break;
    } // this is absolutely right!
  }
  //if(flag == 0) printf("delete failed.3\n");
  user_data.close();
  return ;
}

void Find(const std::string &author, std::vector <int> &ids){
  int choose = -1; 
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].author < author) choose = i;
    else break;
  assert(choose != -1);
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  int flag = 1; book tmp;
  for(int i = choose; i <= cnt; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(tmp.author == author) ids.push_back(tmp.id);
      else if(tmp.author > author){
        flag = 0;
        break;
      }
    }
    if(flag == 0) break;
  }
  user_data.close();
  return ;
}

}

namespace by_key_word{

const int B = 300, L = Book_data_Len;
char space = ' ';
std::fstream user_data, list_data, head_data;
std::string user_data_name = "user_data_4.txt", list_data_name = "list_data_4.txt", head_data_name = "head_data_4.txt";

int head[1005], cnt = 0, siz[1005], nownew = 0;

book Head_data[1005], temp[1005];

void Insert(const book &cur);

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
    book ST;
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

void Insert(const book &cur){
  int choose = -1;
  for(int i = 1; i <= cnt; ++i)
    if(leq_4(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  for(int i = 1; i <= size; ++i){
    temp[i].simple_read(user_data);
    if(leq_4(temp[i], cur)) put = i;
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

void Delete(const book &cur){
  int choose = -1; book tmp;
  for(int i = 1; i <= cnt; ++i)
    if(leq_4(Head_data[i], cur)) choose = i;
    else break;
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  user_data.seekg(head[choose] * sizeof(char), std::ios::beg);
  int flag = 0;
  for(int i = 1; i <= siz[choose]; ++i){
    tmp.simple_read(user_data);
    //if(tmp.key_word == cur.key_word && tmp.id != cur.id) printf("???\n");
    if(tmp.id == cur.id && eq(tmp.key_word, cur.key_word)){
      Delete_any(choose, i);
      flag = 1;
      break;
    } // this is absolutely right!
  }
  //if(flag == 0) printf("delete failed.\n");
  user_data.close();
  return ;
}

void Find(const std::string &key_word, std::vector <int> &ids){
  int choose = -1; 
  for(int i = 1; i <= cnt; ++i)
    if(Head_data[i].key_word < key_word) choose = i;
    else break;
  assert(choose != -1);
  user_data.open(user_data_name, std::ios::in | std::ios::out | std::ios::binary);
  int size = siz[choose], put = 0; 
  int flag = 1; book tmp;
  for(int i = choose; i <= cnt; ++i){
    user_data.seekg(head[i] * sizeof(char), std::ios::beg);
    for(int j = 1; j <= siz[i]; ++j){
      tmp.simple_read(user_data);
      if(tmp.key_word == key_word) ids.push_back(tmp.id);
      else if(tmp.key_word > key_word){
        flag = 0;
        break;
      }
    }
    if(flag == 0) break;
  }
  user_data.close();
  return ;
}

}