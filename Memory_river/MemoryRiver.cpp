#include"MemoryRiver.hpp"
#define pb push_back
#include<iostream>
#include<random>
#include<map>
typedef long long lld;
typedef unsigned long long ull;
const ull bss=65536;
std::map<int,ull> s;
std::map<int,int> l;//last type
std::vector<int>lnr;
ull rdi()//random a ull number
{
    return bss*bss*bss/2*rand()+bss*bss*rand()+rand()*rand();
}
int rdm(int mdx)//random mode
{
    return rand()%mdx;
}
int RIX()//rand an index
{
    int c=rand()%lnr.size();
    return lnr[c];
}
void TER(const char* s,int x)
{
    printf("%s %d\n",s,x);
    exit(0);
}
int main()
{
    //测试程序
    MemoryRiver<ull,2> F("test.dat");
    srand(time(0));
    F.initialize("test.dat");
    for(int i=1;1<=2000;i++)
    {
        if(i%1000==0) printf("%d\n",i);
        int typ=rdm(4);
        if(i==1||typ==0)//insert
        {
            ull x=rdi();
            int index=F.write(x);
            if(index==-1) TER("0A",0);   
            s[index]=x;l[index]=0;lnr.pb(index);
            //lnr
        }
        else if(typ==1)//change
        {
            //continue;
            int index=RIX();ull x=rdi();
            F.update(x,index);
            l[index]=1;s[index]=x;
        }
        else if(typ==2)//read
        {
            int index=RIX();ull x;
            F.read(x,index);
            if(x!=s[index]) printf("%d %llX %llX ",index,x,s[index]),TER("1B",l[index]);
        }
        else//delete
        {
            
        }
    }
    printf("End Check Successfully");
}
/*
错误代码
0A %d
0A 在新加入时返回的索引为-1，文件指针错误。
1B 数据不正确。0表示上次刚加入。1表示上次操作是修改。

12 221FCEDB15F24526
20 9ED5436354849B1
7 9ED5436354849B1 221FCEDB15F24526 1B 0
*/