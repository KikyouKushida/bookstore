#ifndef include_bits
#include "share.hpp"
#define include_bits
#endif

#include "AccountSystem.hpp"
#include "BookSystem.hpp"
#include "LogSystem.hpp"

void Deal(std::string &read_in, std::vector <interval> &info){
  if(read_in.size() == 0) return ;
  info.clear();
  std::string tmp; int len = read_in.size();
  for(int i = 0, j; i < read_in.size(); i = j + 1){
    j = i;
    if(read_in[j] == ' ') continue;
    while(j + 1 < read_in.size() && read_in[j + 1] != ' ') ++j;
    int this_len = j - i + 1;
    if(info.size() == 0){
      info.push_back(interval(0, this_len - 1));
      tmp += read_in.substr(i, this_len);
    }
    else {
      info.push_back(interval(info[info.size() - 1].r + 2, info[info.size() - 1].r + 2 + this_len - 1));
      tmp += ' '; 
      tmp += read_in.substr(i, this_len);
    }
  }
  std::swap(tmp, read_in);
  return ;
}

const std::string share_data_name = "share.txt";
std::fstream share_data;

void Initialize(){
  block::Initialize();
  by_ISBN::Initialize();
  by_book_name::Initialize();
  by_author::Initialize();
  by_key_word::Initialize();
  std::ifstream ifile;
  ifile.open(Book_data_name);
  if(!ifile){
    Book_data.open(Book_data_name, std::ios::out | std::ios::binary);
    Book_data.close();
    book ST;
    ST.write(Book_data, Book_data_name, 0);
  }
  else ifile.close();
  ifile.open(share_data_name);
  if(!ifile){
    share_data.open(share_data_name, std::ios::out | std::ios::binary);
    share_data.close();
  }
  else {
    ifile.close();
    share_data.open(share_data_name, std::ios::in | std::ios::out | std::ios::binary);
    share_data.seekg(0, std::ios::beg);
    share_data.read(reinterpret_cast<char *>(&Book_count), 4 * sizeof(char));
    share_data.read(reinterpret_cast<char *>(&trade_count), 4 * sizeof(char));
    for(int i = 1; i <= trade_count; ++i){
      share_data.read(reinterpret_cast<char *>(&f[i]), 8 * sizeof(char));
      share_data.read(reinterpret_cast<char *>(&g[i]), 8 * sizeof(char));
    }
    int size;
    share_data.read(reinterpret_cast<char *>(&size), 4 * sizeof(char));
    for(int i = 0; i < size; ++i){
      log_in.push_back(account());
      log_in[log_in.size() - 1].simple_read(share_data);
    }
    update_current_privilege();
    share_data.close();
  }
  return ;
}

void Share_store(){
  share_data.open(share_data_name, std::ios::out | std::ios::binary);
  share_data.seekp(0, std::ios::beg);
  share_data.write(reinterpret_cast<char *>(&Book_count), 4 * sizeof(char));
  share_data.write(reinterpret_cast<char *>(&trade_count), 4 * sizeof(char));
  for(int i = 1; i <= trade_count; ++i){
    share_data.write(reinterpret_cast<char *>(&f[i]), 8 * sizeof(char));
    share_data.write(reinterpret_cast<char *>(&g[i]), 8 * sizeof(char));
  }
  int size = (int)log_in.size();
  share_data.write(reinterpret_cast<char *>(&size), 4 * sizeof(char));
  for(int i = 0; i < size; ++i) log_in[i].simple_write(share_data);
  share_data.close();
  return ;
}

int main(){
  //freopen("./bookstore-testcases/basic/testcase8/11.in", "r", stdin);
  //freopen("testcase6.in", "r", stdin);
  //freopen("out.txt", "w", stdout);
  std::string read_in;
  std::vector <interval> info;
  Initialize();
  int query_count = 0;
  while(true){
    getline(std::cin, read_in);
    if(read_in.size() == 0) continue;
    if(read_in[read_in.size() - 1] == '\r') read_in.pop_back();
    Deal(read_in, info);
    //printf("%d : \n", ++query_count);
    //std::cout << (int)read_in[read_in.size() - 1] << " " << read_in << "\n";
    //sleep(0.4);
    if(read_in.size() == 0) continue;
    assert(info.size() >= 1);
    if(info[0] == interval(0, 1) && read_in.substr(0, 2) == "su") LogIn_account(read_in, info);
    else if(read_in == "show") Show_all();
    else if(read_in.substr(0, 12) == "show finance") Show_finance(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "logout") LogOut_account();
    else if(info[0] == interval(0, 7) && read_in.substr(0, 8) == "register") Register_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "passwd") Change_pass_word(read_in, info);
    else if(info[0] == interval(0, 6) && read_in.substr(0, 7) == "useradd") Create_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "delete") Delete_account(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "select") Select_book(read_in, info);
    else if(info[0] == interval(0, 3) && read_in.substr(0, 4) == "show") Show_book(read_in, info);
    else if(info[0] == interval(0, 2) && read_in.substr(0, 3) == "buy") Sell_book(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "import") Import_book(read_in, info);
    else if(info[0] == interval(0, 5) && read_in.substr(0, 6) == "modify") Modify_book(read_in, info);
    else if(read_in == "exit" || read_in == "quit") break;
    else if(read_in == "report finance") Report_finance();
    else if(read_in == "report employee") Report_employee();
    else if(read_in == "log") Log();
    else fail();
    //printf("current_privilege = %d\n", current_privilege);
  }
  block::Store();
  by_ISBN::Store();
  by_book_name::Store();
  by_author::Store();
  by_key_word::Store();
  Share_store();
  return 0;
}