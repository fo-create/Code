#include<stdio.h>
#include<stdlib.h>
#define M 6//����//
#define N 7//����//
#define max 100//����Ԫ�������//
#define MAX ((M)>(N)?(M):(N))//�����нϴ���//
typedef struct
{
	int r, c;//�кţ��к�//
	int data;//Ԫ��ֵ//
}TupNode;
typedef struct
{
	int rows;
	int cols;
	int nums;
	TupNode data[max];
}TSMatrix;
//ʮ������ṹ�����Ͷ���//
typedef struct mtxn
{
	int row;
	int col;
	struct mtxn *right, *down;
	union {
		int value;
		struct mtxn *link;//ָ����һ��ͷ���//
	}tag;
}MatNode;
//�������ж������Ԫ��//
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
//��Ԫ���¼���Ԫ�ؼ���ϡ�����A[i][j]=x//
bool Value(TSMatrix &t, int x, int i, int j)
{
	int k = 0, k1;
	if (i >= t.rows || j >= t.cols)
		return false;
	while (k<t.nums&&i>t.data[k].r)
		k++;//������//
	while (k<t.nums&&i == t.data[k].r&&j>t.data[k].c)
		k++;//������//
	if (t.data[k].r == i && t.data[k].c == j)//������//
		t.data[k].data = x;
	else//�������ڣ������һ��//
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
//��ָ��λ��Ԫ��ֵ��������x//
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
//��Ԫ�������//
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
//�����ת��//
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
				if (a.data[p].c == v)//�е�����//
				{
					b.data[q].r = a.data[p].c;
					b.data[q].c = a.data[p].r;
					b.data[q].data = a.data[p].data;
					q++;
				}
	}
}
//��ϡ��������//
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
		if (a.data[i].r == b.data[j].r)//�к����ʱ//
		{
			if (a.data[i].c < b.data[j].c)//a���к�С��b���к�//
			{
				c.data[k].r = a.data[i].r;
				c.data[k].c = a.data[i].c;
				c.data[k].data = a.data[i].data;
				k++; j++;
			}
			else if (a.data[i].c > b.data[j].c)//a���кŴ���b���к�//
			{
				c.data[k].r = b.data[j].r;
				c.data[k].c = b.data[j].c;
				c.data[k].data = b.data[j].data;
				k++; j++;
			}
			else//�к����ʱ//
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
		else//a���кŴ���b���к�//
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
//ʮ������Ĵ���//
void creatMat(MatNode *&mh, int a[M][N])
{
	int i, j;
	MatNode *h[MAX], *p, *q, *r;
	mh = (MatNode*)malloc(sizeof(MatNode));//����ʮ������ͷ���//
	mh->row = M;
	mh->col = N;
	r = mh;//rָ��β���?//
	for (i = 0; i < MAX; i++)//β�巨����ͷ���h[0],h[1]...ѭ������//
	{
		h[i] = (MatNode *)malloc(sizeof(MatNode));
		h[i]->down = h[i]->right = h[i];//��down right������Ϊѭ����//
		r->tag.link = h[i];//h[i]�ӵ�������//
		r = h[i];
	}
	r->tag.link = mh;//����ͷ��㣬��Ϊѭ������//
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (a[i][j] != 0)
			{
				p=(MatNode *)malloc(sizeof(MatNode));//����һ���½��//
				p->row = i; p->col = j; p->tag.value = a[i][j];
				q = h[i];//�������б��еĲ���λ��//
				while (q->right != h[i] && j > q->right->col)
					q = q->right;
				p->right = q->right; q->right = p;//����б�Ĳ���//
				q = h[i];
				while (q->down != h[i] && i > q->down->row)
					q = q->down;
				p->down = q->down; q->down = p;
			}
		}
	}
}
//���ʮ������//
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