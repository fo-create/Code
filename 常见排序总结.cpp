#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 20
void show(int a[]);
void select(int a[]);
void insert(int a[]);
void bubble(int a[]);
void shell(int a[]);
void Sift(int A[], int i, int n);
void HeapSort(int A[], int n);
void Merge(int R[], int R1[], int low, int m, int high);
void sort(int R[], int R1[], int  left, int right);
void Mergesort(int a[]);
void quicksort(int a[]);
int Partition(int a[], int low, int high);
void qsort(int a[], int low, int high);
void bqsort(int data[], int begin, int end);
void betterquicksort(int a[]);
int MID(int data[], int begin, int end);
int sort(int data[], int begin, int end);
void change(int *a, int *b);
int main()
{
	int data[N] = { 10,9,8,7,6,5,4,32,1323,1313,124,786,3576,234245,13,987698,13,3,2,1 };
	bubble(data);
	select(data);
	insert(data);
	shell(data);
	HeapSort(data, N);
	Mergesort(data);
	quicksort(data);
	betterquicksort(data);
	system("pause");
	return 0;
}
void show(int a[])
{
	for (int i = 0; i < N; i++)
		printf("%d ", a[i]);
}
/**
基本思想：两两比较相邻记录的关键字，如果反序则交换
直到没有反序记录为止
*/
void bubble(int a[])//冒泡排序//
{
	int i, j, temp, flag;
	for (i = 0; i < N-1; i++)
	{
		flag = 1;//定义标记量，满足条件则跳出循环//
		for (j=0;j<N-1-i;j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 0;
			}
		}
		if (flag)
			break;
	}
	printf("bubble:\n");
	show(a);
	printf("\n");
}
/**
通过n-i次关键字的比较，从(n-i+1)个记录中选出关键字最小的记录
并和第i个记录交换
*/
void select(int a[])//选择排序//
{
	int i, j, min,temp;
	for (i = 0; i < N - 1; i++)
	{
		min = i;//假设当前i为最小值下标
		for (j = i + 1; j < N; j++)
		{
			if (a[j] < a[min])
				min = j;//在其之后循环比较，确定最小值下标
		}
		if (min != i)//若最小值不是当前值，则当前值与最小值进行交换
		{
			temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
	printf("select:\n");
	show(a);
	printf("\n");
}
/**
从数组的第二个数据开始往前比较，即一开始用第二个数和他前面的一个比较，
如果 符合条件（比前面的大或者小，自定义），则让他们交换位置。
然后再用第三个数和第二个比较，符合则交换，但是此处还得继续往前比较，
*/
void insert(int a[])
{
	for (int i = 1; i<N; i++) {
		int j = i;//从当前位置开始//
		while (j > 0)//注意边界，要保证j>0
		{
			if (a[j] < a[j - 1]) {//若比前面的小则进行交换
				int temp;
				temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
				j--;//一直向前进行比较，直到不满足条件
			}
			else {
				break;
			}
		}
	}
	printf("Insert:\n");
	show(a);
	printf("\n");
}
/**
希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
随着增量逐渐减少，每组包含的关键词越来越多，
当增量减至1时，整个文件恰被分成一组，算法便终止。
*/
void shell(int a[])//希尔排序——分组的插入排序//
{
	int i, j, temp;
	int gap;
	for (gap = N / 2; gap >= 1; gap /= 2)//gap为步长，每次减少为原来的一半
	{
		for (int k = 0; k < gap; k++)//共有gap组，对每组进行插入排序
		{
			for (i = k+gap; i < N; i += gap)//类比插入排序，只不过每次变化的是gap长
			{
				temp = a[i];
				j = i - gap;
				while (j >= 0 && a[j] > temp)
				{
					a[j + gap] = a[j];
					j -= gap;
				}
				a[j + gap] = temp;
			}
		}
	}
	printf("Shell: \n");
	show(a);
	printf("\n");
}
/*
a.将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;
b.将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;
c.重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，
反复执行调整+交换步骤，直到整个序列有序。
*/
void Sift(int A[], int i, int n)//调整堆,下面方法堆编号从0开始，若从1开始，则为2*i//
{
	int temp = A[i];//取出当前元素
	for ( int k = 2 * i + 1; k < n; k = 2 * k + 1)//从i结点的左子结点开始，即（2i+1）处开始
	{
		if (k + 1 < n&&A[k] < A[k + 1])
			k++;//如果左子结点小于右子结点，k指向右子节点
		if (A[k] > temp)//如果子节点大于父节点，则赋值（不用进行交换
		{
			A[i] = A[k];
			i = k;
		}
		else
			break;
	}
	A[i] = temp;//将temp值放到最终位置
}
void HeapSort(int A[], int n)
{
	int j,temp;
	for (j = (n / 2)-1; j >=0; j--)
		Sift(A, j, n);//建初始堆//
	for (j = n-1; j > 0; j--)
	{
		temp = A[0];
		A[0] = A[j];
		A[j] = temp;//交换堆顶和最后一个元素，即每次将剩余元素中最大者放到最后//
		Sift(A, 0, j);//重新调整堆顶结点为大顶堆//
	}
	printf("Heapsort:\n");
	show(A);
	printf("\n");
}
/*
归并排序（MERGE-SORT）是利用归并的思想实现的排序方法，该算法采用经典的分治策略
（分治法将问题分(divide)成一些小的问题然后递归求解，
而治(conquer)的阶段则将分的阶段得到的各答案"修补"在一起，即分而治之)。
*/
void Merge(int R[], int R1[], int low, int mid, int high)
{
	//R[low...m],和R[m+1...high]两个有序表//
	int i = low, j = mid + 1, t = 0;//i，j为两个有序表的下标，t为临时数组指针//
	while (i <= mid && j <= high)
	{
		if (R[i] <= R[j])
		{
			R1[t] = R[i];
			i++;
			t++;
		}
		else
		{
			R1[t] = R[j];
			j++;
			t++;
		}
	}
	while (i <= mid)//将左边剩余元素填充进R1数组中
	{
		R1[t] = R[i];
		i++;
		t++;
	}
	while (j <= high)//将有边序列剩余元素填充进R1中
	{
		R1[t] = R[j];
		j++;
		t++;
	}
	t = 0;
	while (low <= high)
		R[low++] = R1[t++];//将R1中元素全部拷贝到原数组中
}
void sort(int R[], int R1[], int  left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		sort(R, R1, left, mid);//左边序列排序
		sort(R, R1, mid + 1, right);//右边
		Merge(R, R1, left, mid, right);//将两有序子数组合并
	}
}
void Mergesort(int a[])
{
	int b[N];
	sort(a, b, 0, N - 1);
	printf("Mergesort:\n");
	show(a);
	printf("\n");
}
/*
设置两个变量 low、high，排序开始时：low=0，high=size-1。
整个数组找基准正确位置，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面
*/
void quicksort(int a[])
{
	qsort(a, 0, N - 1);
	printf("quicksort:\n");
	show(a);
	printf("\n");
}
int Partition(int a[], int low, int high)
{
	int temp;
	int k = a[low];
	int i = low;
	int j = high + 1;
	while (i < j)
	{
		i = i + 1;
		while (a[i] <= k)
			i = i + 1;
		j = j - 1;
		while (a[j] > k)
			j = j - 1;
		if (i < j)
		{

			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	temp = a[low];
	a[low] = a[j];
	a[j] = temp;
	return j;
}
void qsort(int a[], int low, int high)
{
	if (low < high)
	{
		int pos = Partition(a, low, high);
		qsort(a, low, pos - 1);
		qsort(a, pos + 1, high);
	}
}

int MID(int data[], int begin, int end)
{
	int l, r, mid;
	l = begin;
	r = end;
	mid = begin + ((end - begin) / 2);
	if (data[l] < data[mid])
	{
		if (data[r] > data[mid])
			return mid;
		if (data[l] < data[r])
			return r;
		else
			return l;
	}
	else
	{
		if (data[r] < data[mid])
			return mid;
		if (data[r] > data[l])
			return l;
		else
			return r;
	}
}
int sort(int data[], int begin, int end)
{
	int l, r, mid, temp;
	l = begin;
	r = end;
	mid = MID(data, begin, end);
	change(&data[mid], &data[end]);
	temp = data[end];
	while (l < r)
	{
		while (l < r&&data[l] <= temp)
		{
			l++;
		}
		while (l < r&&data[r] >= temp)
		{
			r--;
		}
		if (data[l] > data[r])
		{
			change(&data[l], &data[r]);
		}
	}
	change(&data[l], &data[end]);
	return l;
}
void change(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void bqsort(int data[], int begin, int end)
{
	if (begin < end)
	{
		int pos = sort(data, begin, end);
		bqsort(data, begin, pos - 1);
		bqsort(data, pos + 1, end);
	}
}
void betterquicksort(int a[])
{
	bqsort(a, 0, N - 1);
	printf("betterquicksort:\n");
	show(a);
	printf("\n");
}

