#include<stdio.h>
#include<stdlib.h>
#define success 1
#define unsuccess 0
#define hashsize 12//定义散列表长为数组的长度//
#define nullkey -32768
typedef struct 
{
    int *elem;//数据元素存储基址，动态分配数组//
    int cnt;//当前数据元素个数//
}Hashtable;
int m=0;//散列表长//
bool initHashtable(Hashtable *H);
int Hash(int key);
void InsertHash(Hashtable *H,int key);
int SearchHash(Hashtable H,int key);
int main()
{
    int a[12]={12,67,56,16,25,37,22,29,15,47,48,34};
    Hashtable H;
    initHashtable(&H);
    for(int i=0;i<12;i++)
    {
        InsertHash(&H,a[i]);
    }
    printf("%d\n",SearchHash(H,60));//???//
    for(int i=0;i<hashsize;i++)
    {
        printf("%d ",H.elem[i]);
    }
    system("pause");
    return 0;
}
//初始化散列表//
bool initHashtable(Hashtable *H)
{
    int i;
    m=hashsize;
    H->cnt=m;
    H->elem=(int *)malloc(m*sizeof(int));
    for(i=0;i<m;i++)
        H->elem[i]=nullkey;
    return true;
}
//定义散列函数//
int Hash(int key)       
{
    return key%m;//取余法//
}
//输入关键字建表//
void InsertHash(Hashtable *H,int key)
{
    int addr=Hash(key);//求散列地址//
    while(H->elem[addr]!=nullkey)//有冲突，开放地址的线性探测//
        addr=(addr+1)%m;
    H->elem[addr]=key;
}
//散列表查找关键字，返回下标//
int SearchHash(Hashtable H,int key)
{
    int addr;
    addr=Hash(key);//求散列地址//
    while(H.elem[addr]!=key)//没对应上，可能有冲突//
    {
        addr=(addr+1)%m;
        if(H.elem[addr]==nullkey||addr==Hash(key))//若循环到空或者回到自己，失败//
        {
            printf("search fail!\n");
           return 0;//？？？查找失败时只输出提示信息？？？//
        }
    }
    return addr;
}