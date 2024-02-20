#ifndef include_bits
#include "share.hpp"
#define include_bits
#endif

std::fstream Book_data;
const std::string Book_data_name = "Book_data.txt";
const int Book_data_Len = 220;

class book{
public:
  char ISBN[22], book_name[62], author[62], key_word[62];
  double price;
  long long num; 
  int id;
  book(){
    for(int i = 0; i < 21; ++i) ISBN[i] = 0;
    for(int i = 0; i < 61; ++i) book_name[i] = author[i] = key_word[i] = 0;
    price = 0.00;
    num = 0ll;
    id = 0;
  }
  book(const std::string &a, const std::string &b = "", const std::string &c = "", const std::string &d = "", const double e = 0.00, const long long f = 0, const int g = 0){
    for(int i = 0; i < 21; ++i) ISBN[i] = 0;
    for(int i = 0; i < 61; ++i) book_name[i] = author[i] = key_word[i] = 0;
    for(int i = 0; i < a.size(); ++i) ISBN[i] = a[i];
    for(int i = 0; i < b.size(); ++i) book_name[i] = b[i];
    for(int i = 0; i < c.size(); ++i) author[i] = c[i];
    for(int i = 0; i < d.size(); ++i) key_word[i] = d[i];
    price = e;
    num = f;
    id = g;
  }
  book(int id){
    book();
    read(Book_data, Book_data_name, Book_data_Len * (id - 1));
  }
  book &operator=(const book &other){
    for(int i = 0; i < 21; ++i) ISBN[i] = other.ISBN[i];
    for(int i = 0; i < 61; ++i) book_name[i] = other.book_name[i];
    for(int i = 0; i < 61; ++i) author[i] = other.author[i];
    for(int i = 0; i < 61; ++i) key_word[i] = other.key_word[i];
    price = other.price;
    num = other.num;
    id = other.id;
    return *this;
  }
  friend bool operator==(const book &a, const book &b){
    for(int i = 0; i < 20; ++i) if(a.ISBN[i] ^ b.ISBN[i]) return false;
    return true; 
  }
  friend bool operator<(const book &a, const book &b){
    for(int i = 0; i < 20; ++i)
      if(a.ISBN[i] < b.ISBN[i]) return true;
      else if(a.ISBN[i] > b.ISBN[i]) return false;
    return false; 
  }
  friend bool operator<=(const book &a, const book &b){
    for(int i = 0; i < 20; ++i)
      if(a.ISBN[i] < b.ISBN[i]) return true;
      else if(a.ISBN[i] > b.ISBN[i]) return false;
    return true; 
  }
  friend bool operator>(const book &a, const book &b){
    return b < a;
  }
  friend bool operator>=(const book &a, const book &b){
    return b <= a;
  }
  void read(std::fstream &file, const std::string &file_name, const int &index){
    file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    file.seekg(index * sizeof(char), std::ios::beg);
    file.read(reinterpret_cast<char *>(&ISBN), 20 * sizeof(char));
    file.read(reinterpret_cast<char *>(&book_name), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&author), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&key_word), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&price), 8 * sizeof(char));
    file.read(reinterpret_cast<char *>(&num), 8 * sizeof(char));
    file.read(reinterpret_cast<char *>(&id), 4 * sizeof(char));
    file.close();
    return ;
  }
  void write(std::fstream &file, const std::string &file_name, const int &index){
    file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);
    file.seekp(index * sizeof(char), std::ios::beg);
    file.write(reinterpret_cast<char *>(&ISBN), 20 * sizeof(char));
    file.write(reinterpret_cast<char *>(&book_name), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&author), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&key_word), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&price), 8 * sizeof(char));
    file.write(reinterpret_cast<char *>(&num), 8 * sizeof(char));
    file.write(reinterpret_cast<char *>(&id), 4 * sizeof(char));
    file.close();
    return ;
  }
  void simple_read(std::fstream &file){
    file.read(reinterpret_cast<char *>(&ISBN), 20 * sizeof(char));
    file.read(reinterpret_cast<char *>(&book_name), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&author), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&key_word), 60 * sizeof(char));
    file.read(reinterpret_cast<char *>(&price), 8 * sizeof(char));
    file.read(reinterpret_cast<char *>(&num), 8 * sizeof(char));
    file.read(reinterpret_cast<char *>(&id), 4 * sizeof(char));
    return ;
  }
  void simple_write(std::fstream &file){
    file.write(reinterpret_cast<char *>(&ISBN), 20 * sizeof(char));
    file.write(reinterpret_cast<char *>(&book_name), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&author), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&key_word), 60 * sizeof(char));
    file.write(reinterpret_cast<char *>(&price), 8 * sizeof(char));
    file.write(reinterpret_cast<char *>(&num), 8 * sizeof(char));
    file.write(reinterpret_cast<char *>(&id), 4 * sizeof(char));
    return ;
  }
  friend bool leq_1(const book &a, const book &b){
    return a <= b;
  }
  friend bool leq_2(const book &a, const book &b){
    int la = strlen(a.book_name), lb = strlen(b.book_name);
    for(int i = 0; i < std::min(la, lb); ++i) 
      if(a.book_name[i] < b.book_name[i]) return true;
      else if(a.book_name[i] > b.book_name[i]) return false;
    if(la < lb) return true;
    else if(la > lb) return false;
    return a.id <= b.id;
  } 
  friend bool leq_3(const book &a, const book &b){
    int la = strlen(a.author), lb = strlen(b.author);
    for(int i = 0; i < std::min(la, lb); ++i) 
      if(a.author[i] < b.author[i]) return true;
      else if(a.author[i] > b.author[i]) return false;
    if(la < lb) return true;
    else if(la > lb) return false;
    return a.id <= b.id;
  } 
  friend bool leq_4(const book &a, const book &b){
    int la = strlen(a.key_word), lb = strlen(b.key_word);
    for(int i = 0; i < std::min(la, lb); ++i) 
      if(a.key_word[i] < b.key_word[i]) return true;
      else if(a.key_word[i] > b.key_word[i]) return false;
    if(la < lb) return true;
    else if(la > lb) return false;
    return a.id <= b.id;
  } 
};

void Show_one(const book &cur);

int Book_count = 0;

bool check_ISBN(const std::string &a){
  if(a.size() > 20) return false;
  for(int i = 0; i < a.size(); ++i) if(a[i] == 127 || (a[i] >= 0 && a[i] <= 32)) return false;
  return true;
}

bool check_book_name_or_author(const std::string &a){
  if(a.size() > 60) return false;
  for(int i = 0; i < a.size(); ++i) if(a[i] == 127 || (a[i] >= 0 && a[i] <= 32) || a[i] == '"') return false;
  return true;
}

bool check_key_word_1(const std::string &a){
  if(a.size() > 60) return false;
  if(a.size() == 0) return true;
  if(a[0] == '|' || a[a.size() - 1] == '|') return false;
  for(int i = 0; i < a.size(); ++i) if(a[i] == 127 || (a[i] >= 0 && a[i] <= 32) || a[i] == '"') return false;
  for(int i = 0; i < a.size() - 1; ++i) if(a[i] == '|' && a[i + 1] == '|') return false;
  return true;
}

bool check_quantity(const std::string &a){
  if(a.size() < 1 || a.size() > 10) return false;
  for(int i = 0; i < a.size(); ++i) if(!isdigit(a[i])) return false;
  if(a.size() < 10) return true;
  for(int i = 0; i < 10; ++i) if(a[i] < INT_MAX_[i]) return true; else if(a[i] > INT_MAX_[i]) return false;
  return true;
} 

bool check_key_word_2(std::vector <std::string> &info){
  if(info.size() <= 1) return true;
  std::sort(info.begin(), info.end());
  for(int i = 0; i < info.size() - 1; ++i) if(info[i] == info[i + 1]) return false;
  return true;
}

bool check_price_or_total_cost(const std::string &a){
  if(a.size() > 13 && a.size() < 1) return false;
  int count = 0;
  for(int i = 0; i < a.size(); ++i) count += a[i] == '.';
  if(count > 1) return false;
  for(int i = 0; i < a.size(); ++i) if(a[i] != '.' && !isdigit(a[i])) return false;
  for(int i = 0; i < a.size(); ++i) if(a[i] == '.' && a.size() - i - 1 > 2) return false;
  if(a[0] == '.') return false;
  return true;
}

int Get_quantity(const std::string &a){
  int res = 0;
  for(int i = 0; i < a.size(); ++i) res *= 10, res += a[i] - '0';
  return res;
}

double Get_price_or_total_cost(const std::string &a){
  double res = 0.00;
  for(int i = 0; i < a.size(); ++i) if(a[i] != '.') res *= 10, res += a[i] - '0';
  for(int i = 0; i < a.size(); ++i) if(a[i] == '.') for(int j = 1; j <= a.size() - 1 - i; ++j) res /= 10.00;
  return res;
}

void Get_key_word(const std::string &a, std::vector <std::string> &key_value){
  key_value.clear();
  if(a.size() == 0) return ;
  int lst = -1;
  for(int i = 0; i < a.size(); ++i) if(a[i] == '|') key_value.push_back(a.substr(lst + 1, i - lst - 1)), lst = i;
  key_value.push_back(a.substr(lst + 1, a.size() - lst - 1));
  return ;
}

#include "Search_by_four_ways.hpp"

void Create_book(const std::string &ISBN){
  Book_count += 1;
  //printf("%d\n", (int)ISBN.size());
  book new_book(ISBN); new_book.id = Book_count;
  //printf("%d\n", (int)strlen(new_book.ISBN));
  new_book.write(Book_data, Book_data_name, (Book_count - 1) * Book_data_Len);
  //printf("%d %d\n", (int)strlen(new_book.book_name), (int)strlen(new_book.author));
  //printf("Create %d:\n", Book_count);
  //Show_one(new_book);
  by_ISBN::Insert(new_book);
  by_book_name::Insert(new_book);
  by_author::Insert(new_book);
  //by_key_word::Insert(new_book);
  return ;
}

void Select_book(const std::string &read_in, const std::vector <interval> &info){
  if(log_in.size() == 0 || info.size() != 2){
    fail();
    return ;
  }
  std::string ISBN = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_ISBN(ISBN)){
    fail();
    return ;
  }
  book now; by_ISBN::get_info(ISBN, now);
  if(now.id == -1){
    Create_book(ISBN);
    by_ISBN::get_info(ISBN, now);
  }
  log_in[log_in.size() - 1].select = now.id;
  return ;
}

void Erase_book(const book &cur){
  by_ISBN::Delete(cur.ISBN);
  by_book_name::Delete(cur);
  by_author::Delete(cur);
  std::vector <std::string> key_value;
  Get_key_word(cur.key_word, key_value);
  for(auto v: key_value){
    book now; now = cur;
    for(int i = 0; i < 61; ++i) now.key_word[i] = 0;
    for(int i = 0; i < v.size(); ++i) now.key_word[i] = v[i];
    by_key_word::Delete(now);
  }
  return ;
}

void Add_book(book &cur){
  cur.write(Book_data, Book_data_name, (cur.id - 1) * Book_data_Len);
  by_ISBN::Insert(cur);
  by_book_name::Insert(cur);
  by_author::Insert(cur);
  std::vector <std::string> key_value;
  Get_key_word(cur.key_word, key_value);
  for(auto v: key_value){
    book now; now = cur;
    for(int i = 0; i < 61; ++i) now.key_word[i] = 0;
    for(int i = 0; i < v.size(); ++i) now.key_word[i] = v[i];
    by_key_word::Insert(now);
  }
  return ;
}

void Sell_book(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 3){
    fail();
    return ;
  }
  std::string ISBN = read_in.substr(info[1].l, info[1].r - info[1].l + 1);
  if(!check_ISBN(ISBN)){
    fail();
    return ;
  }
  if(!check_quantity(read_in.substr(info[2].l, info[2].r - info[2].l + 1))){
    fail();
    return ;
  }
  book now; by_ISBN::get_info(ISBN, now);
  if(now.id == -1){
    fail();
    return ;
  }
  int quantity = Get_quantity(read_in.substr(info[2].l, info[2].r - info[2].l + 1));
  if(now.num < quantity){
    fail();
    return ;
  }
  Erase_book(now);
  now.num -= 1ll * quantity;
  printf("%.2lf\n", 1.0 * quantity * now.price);
  trade_count += 1;
  f[trade_count] = f[trade_count - 1] + 1.0 * quantity * now.price,
  g[trade_count] = g[trade_count - 1];
  Add_book(now);
  return ;
}

void Import_book(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 3){
    fail();
    return ;
  }
  if(!log_in.size() || log_in[log_in.size() - 1].select == 0){
    fail();
    return ;
  }
  if(!check_quantity(read_in.substr(info[1].l, info[1].r - info[1].l + 1))){
    fail();
    return ;
  }
  if(!check_price_or_total_cost(read_in.substr(info[2].l, info[2].r - info[2].l + 1))){
    fail();
    return ;
  }
  int id = log_in[log_in.size() - 1].select;
  int quantity = Get_quantity(read_in.substr(info[1].l, info[1].r - info[1].l + 1));
  double total_cost = Get_price_or_total_cost(read_in.substr(info[2].l, info[2].r - info[2].l + 1));
  book now(id);
  Erase_book(now);
  now.num += quantity;
  trade_count += 1;
  f[trade_count] = f[trade_count - 1],
  g[trade_count] = g[trade_count - 1] + total_cost;
  Add_book(now);
  return ;
}

void Show_one(const book &cur){
  //printf("size %d %d %d %d\n", (int)strlen(cur.ISBN), (int)strlen(cur.book_name), (int)strlen(cur.author), (int)strlen(cur.key_word));
  printf("%s\t%s\t%s\t%s\t%.2lf\t%lld\n", cur.ISBN, cur.book_name, cur.author, cur.key_word, cur.price, cur.num);
  return ;
}

void Show_one(const int &id){
  book cur; cur.read(Book_data, Book_data_name, (id - 1) * Book_data_Len * sizeof(char));
  Show_one(cur);
  return ;
}

void Show_one(const std::string &ISBN){
  book cur; by_ISBN::get_info(ISBN, cur);
  if(cur.id == -1){
    printf("\n");
    return ;
  }
  Show_one(cur);
  return ;
}

void Show_all(){
  if(Book_count == 0){
    printf("\n");
    return ;
  }
  by_ISBN::Show_all();
  return ;
}

void Show_ISBN(const std::string &cur){
  if(!check_ISBN(cur)){
    fail();
    return ;
  }
  Show_one(cur);
  return ;
}

void Show_book_name(const std::string &cur){
  if(!check_book_name_or_author(cur)){
    fail();
    return ;
  }
  std::vector <int> ids; by_book_name::Find(cur, ids);
  if(ids.size() == 0) printf("\n");
  else for(auto id: ids) Show_one(id);
  return ;
}

void Show_author(const std::string &cur){
  if(!check_book_name_or_author(cur)){
    fail();
    return ;
  }
  std::vector <int> ids; by_author::Find(cur, ids);
  if(ids.size() == 0) printf("\n");
  else for(auto id: ids) Show_one(id);
  return ;
}

void Show_key_word(const std::string &cur){
  if(!check_key_word_1(cur)){
    fail();
    return ;
  }
  for(int i = 0; i < cur.size(); ++i) 
    if(cur[i] == '|'){
      fail();
      return ;
    }
  std::vector <int> ids; by_key_word::Find(cur, ids);
  if(ids.size() == 0) printf("\n");
  else for(auto id: ids) Show_one(id);
  return ;
}

void Show_book(const std::string &read_in, const std::vector <interval> &info){
  if(info.size() != 2){
    fail();
    return ;
  }
  int len = read_in.size();
  if(len >= 12 && read_in.substr(5, 6) == "-ISBN=") Show_ISBN(read_in.substr(11, len - 11));
  else if(len >= 14 && read_in.substr(5, 7) == "-name=\"" && read_in[len - 1] == '"') Show_book_name(read_in.substr(12, len - 13));
  else if(len >= 16 && read_in.substr(5, 9) == "-author=\"" && read_in[len - 1] == '"') Show_author(read_in.substr(14, len - 15));
  else if(len >= 17 && read_in.substr(5, 10) == "-keyword=\"" && read_in[len - 1] == '"') Show_key_word(read_in.substr(15, len - 16));
  else fail();
  return ;
}

int Get_form(const std::string &a){
  if(a.size() >= 7 && a.substr(0, 6) == "-ISBN=") return 0;
  if(a.size() >= 9 && a.substr(0, 7) == "-name=\"" && a[a.size() - 1] == '"') return 1;
  if(a.size() >= 11 && a.substr(0, 9) == "-author=\"" && a[a.size() - 1] == '"') return 2;
  if(a.size() >= 12 && a.substr(0, 10) == "-keyword=\"" && a[a.size() - 1] == '"') return 3;
  if(a.size() >= 8 && a.substr(0, 7) == "-price=") return 4;
  return -1;
}

void Modify_book(const std::string &read_in, const std::vector <interval> &info){
  if(!log_in.size() || log_in[log_in.size() - 1].select == 0){
    fail();
    //printf("f1 %d\n", (int)log_in.size());
    return ;
  }
  if(info.size() < 2 || info.size() > 6){
    fail();
    //printf("f2\n");
    return ;
  }
 // printf("ok begin modify. %d\n", log_in[log_in.size() - 1].select);
  book old_one(log_in[log_in.size() - 1].select), new_one;
  new_one = old_one;
  int has_changed[5] = {0, 0, 0, 0, 0};
  for(int i = 1; i < info.size(); ++i){
    std::string This = read_in.substr(info[i].l, info[i].r - info[i].l + 1);
    int form = Get_form(This);
    if(form == -1 || has_changed[form] == 1){
      fail();
      //printf("form error on i = %d, form = %d.\n", i, form);
      return ;
    }
    //printf("form = %d, has = %d\n", form, has_changed[form]);
    has_changed[form] = 1;
    if(form == 0){
      std::string new_ISBN = This.substr(6, This.size() - 6);
      if(!check_ISBN(new_ISBN)){
        fail();
        return ;
      }
      book tmp; by_ISBN::get_info(new_ISBN, tmp);
      if(tmp.id != -1){
        fail();
        return ;
      }
      Give(new_one.ISBN, new_ISBN);
    }
    else if(form == 1){
      std::string new_book_name = This.substr(7, This.size() - 8);
      if(!check_book_name_or_author(new_book_name)){
        fail();
        return ;
      }
      Give(new_one.book_name, new_book_name);
    }
    else if(form == 2){
      std::string new_author = This.substr(9, This.size() - 10);
      if(!check_book_name_or_author(new_author)){
        fail();
        return ;
      }
      Give(new_one.author, new_author);
    }
    else if(form == 3){
      std::string new_key_word = This.substr(10, This.size() - 11);
      if(!check_key_word_1(new_key_word)){
        fail();
        return ;
      }
      std::vector <std::string> new_key_value;
      Get_key_word(new_key_word, new_key_value);
      if(!check_key_word_2(new_key_value)){
        fail();
        return ;
      }
      Give(new_one.key_word, new_key_word);
    }
    else if(form == 4){
      std::string new_price = This.substr(7, This.size() - 7);
      if(!check_price_or_total_cost(new_price)){
        fail();
        return ;
      }
      new_one.price = Get_price_or_total_cost(new_price);
    }
  }
  //printf("ok end modify.\n");
  //printf("old:"); Show_one(old_one);
  //printf("\n");
  //printf("new:"); Show_one(new_one);
  //printf("\n");
  Erase_book(old_one);
  Add_book(new_one);
  return ;
}
