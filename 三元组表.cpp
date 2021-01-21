#include<stdio.h>
#include<stdlib.h>
#define M 6//行数//
#define N 7//列数//
#define max 100//非零元素最多数//
#define MAX ((M)>(N)?(M):(N))//行列中较大者//
typedef struct
{
	int r, c;//行号，列号//
	int data;//元素值//
}TupNode;
typedef struct
{
	int rows;
	int cols;
	int nums;
	TupNode data[max];
}TSMatrix;
//十字链表结构体类型定义//
typedef struct mtxn
{
	int row;
	int col;
	struct mtxn *right, *down;
	union {
		int value;
		struct mtxn *link;//指向下一个头结点//
	}tag;
}MatNode;
//从数组中读入非零元素//
void creat(TSMatrix &t, int A[M][N])
{
	int i, j;
	t.rows = M;
	t.cols = N;
	t.nums = 0;
	for (i = 0; i < M; i++)
	{
		for(j=0;j<N;j++)
			if (A[i][j] != 0)
			{
				t.data[t.nums] .r= i;
				t.data[t.nums].c = j;
				t.data[t.nums].data = A[i][j];
				t.nums++;
			}
	}
}
//三元组新加入元素即对稀疏矩阵A[i][j]=x//
bool Value(TSMatrix &t, int x, int i, int j)
{
	int k = 0, k1;
	if (i >= t.rows || j >= t.cols)
		return false;
	while (k<t.nums&&i>t.data[k].r)
		k++;//查找行//
	while (k<t.nums&&i == t.data[k].r&&j>t.data[k].c)
		k++;//查找列//
	if (t.data[k].r == i && t.data[k].c == j)//若存在//
		t.data[k].data = x;
	else//若不存在，则插入一个//
	{
		for (k1 = t.nums - 1; k1 >= k; k1--)
		{
			t.data[k1 + 1].r = t.data[k1].r;
			t.data[k1 + 1].c = t.data[k1].c;
			t.data[k1 + 1].data = t.data[k1].data;
		}
		t.data[k].r = i;
		t.data[k].c = j;
		t.data[k].data = x;
		t.nums++;
	}
	return true;
}
//将指定位置元素值赋给变量x//
bool Assign(TSMatrix t, int &x, int i, int j)
{
	int k = 0;
	if (i >= t.rows || j >= t.cols)
		return false;
	while (i > t.data[k].r&&k < t.nums)
		k++;
	while (k<t.nums&&i == t.data[k].r&&j>t.data[k].c)
		k++;
	if (i == t.data[k].r&&j == t.data[k].c)
		x = t.data[k].data;
	else
		x = 0;
	return true;
}
//三元组表的输出//
void out(TSMatrix t)
{
	int i;
	if (t.nums <= 0)
		return;
	printf("%4d%4d%4d\n", t.nums, t.rows, t.cols);
	for (i = 0; i < t.nums; i++)
	{
		printf("%2d%2d%2d\n", t.data[i].r, t.data[i].c, t.data[i].data);
	}
}
//矩阵的转置//
void trans(TSMatrix a, TSMatrix &b)
{
	int p, q = 0, v;
	b.cols = a.rows;
	b.rows = a.cols;
	b.nums = a.nums;
	if (a.nums != 0)
	{
		for(v=0;v<a.cols;v++)
			for(p=0;p<a.nums;p++)
				if (a.data[p].c == v)//行等于列//
				{
					b.data[q].r = a.data[p].c;
					b.data[q].c = a.data[p].r;
					b.data[q].data = a.data[p].data;
					q++;
				}
	}
}
//两稀疏矩阵相加//
bool add(TSMatrix a, TSMatrix b, TSMatrix &c)
{
	int i = 0, j = 0, k = 0;
	int v;
	if (a.rows != b.rows || a.cols != b.cols)
		return false;
	c.rows = a.rows;
	c.cols = a.cols;
	while (i < a.nums&&j < b.nums)
	{
		if (a.data[i].r == b.data[j].r)//行号相等时//
		{
			if (a.data[i].c < b.data[j].c)//a的列号小于b的列号//
			{
				c.data[k].r = a.data[i].r;
				c.data[k].c = a.data[i].c;
				c.data[k].data = a.data[i].data;
				k++; j++;
			}
			else if (a.data[i].c > b.data[j].c)//a的列号大于b的列号//
			{
				c.data[k].r = b.data[j].r;
				c.data[k].c = b.data[j].c;
				c.data[k].data = b.data[j].data;
				k++; j++;
			}
			else//列号相等时//
			{
				v = a.data[i].data + b.data[j].data;
				if (v != 0)
				{
					c.data[k].r = a.data[i].r;
					c.data[k].c = a.data[i].c;
					c.data[k].data = v;
					k++;
				}
				i++; j++;
			}
		}
		else if (a.data[i].r < b.data[j].r)
		{
			c.data[k].r = a.data[i].r;
			c.data[k].c = a.data[i].c;
			c.data[k].data = a.data[i].data;
			k++; i++;
		}
		else//a的行号大于b的行号//
		{
			c.data[k].r = b.data[j].r;
			c.data[k].c = b.data[j].c;
			c.data[k].data = b.data[j].data;
			k++; j++;
		}
		c.nums = k;
	}
	return true;
}
//十字链表的创建//
void creatMat(MatNode *&mh, int a[M][N])
{
	int i, j;
	MatNode *h[MAX], *p, *q, *r;
	mh = (MatNode*)malloc(sizeof(MatNode));//创建十字链表头结点//
	mh->row = M;
	mh->col = N;
	r = mh;//r指向尾结点?//
	for (i = 0; i < MAX; i++)//尾插法创建头结点h[0],h[1]...循环链表//
	{
		h[i] = (MatNode *)malloc(sizeof(MatNode));
		h[i]->down = h[i]->right = h[i];//将down right方向置为循环的//
		r->tag.link = h[i];//h[i]加到链表中//
		r = h[i];
	}
	r->tag.link = mh;//连到头结点，置为循环链表//
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (a[i][j] != 0)
			{
				p=(MatNode *)malloc(sizeof(MatNode));//创建一个新结点//
				p->row = i; p->col = j; p->tag.value = a[i][j];
				q = h[i];//查找在行表中的插入位置//
				while (q->right != h[i] && j > q->right->col)
					q = q->right;
				p->right = q->right; q->right = p;//完成行表的插入//
				q = h[i];
				while (q->down != h[i] && i > q->down->row)
					q = q->down;
				p->down = q->down; q->down = p;
			}
		}
	}
}
//输出十字链表//
void outMat(MatNode *mh)
{
	MatNode *p, *q;
	printf("row=%d col=%d", mh->row, mh->col);
	p = mh->tag.link;
	while (p != mh)
	{
		q = p->right;
		while (p != q)
		{
			printf("%d %d %d", q->row, q->col, q->tag.value);
			q = q->right;
		}
		p = p->tag.link;
	}
}