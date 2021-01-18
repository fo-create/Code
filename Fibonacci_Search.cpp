#include<stdio.h>
#include<stdlib.h>
int data[20] = {0};
int createFibonacci(int n);
int Fibonacci_Search(int a[], int n, int key);
int main()
{
	
	for (int i = 1; i <= 20; i++)
		data[i] = createFibonacci(i);//首先构造全局斐波那契数列//
	int a[11]={0,1,2,3,4,5,6,7,8,9,10};
	int pos=Fibonacci_Search(a,10,4);
	printf("%d\n",pos);
	system("pause");
	return 0;
}
int createFibonacci(int n)
{
	if (n == 1 || n == 2)
		return 1;
	else
		return createFibonacci(n - 1) + createFibonacci(n - 2);
}
int Fibonacci_Search(int a[], int n, int key)
{
	int low, high, mid, i, k;
	low = 1;
	high = n;
	k = 0;
	while (n > data[k] - 1)//计算n在数列中的位置//
		k++;
	for (i = n; i < data[k] - 1; i++)//将不满的数值补全//
		a[i] = a[n];
	while (low <= high)
	{
		mid = low + data[k - 1] - 1;//计算当前分隔符的下标//
		if (key < a[mid])
		{
			high = mid - 1;
			k = k - 1;//斐波那契数列下标减小一位//
		}
		else if (key > a[mid])
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if (mid <= n)
				return mid;
			else
			{
				return n;//mid>n说明为补全数值，返回n//
			}
		}
	}
}
