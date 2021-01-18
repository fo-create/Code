#include<stdio.h>
#include<stdlib.h>
int Binary_search(int a[],int low,int high,int key);//折半查找，前提为有序表//
int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int pos=Binary_search(a,1,10,1);
      printf("%d\n",pos);
      system("pause");
    return 0;
}
int Binary_search(int a[],int low,int high,int key)//折半查找，返回下标，前提为有序表//
{
    int mid=(low+high)/2;
    if(a[mid]==key)
        return mid;
    else if(a[mid]>key)
        Binary_search(a,low,mid-1,key);
    else
        Binary_search(a,mid+1,high,key);
}