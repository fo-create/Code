#include<cstdio>
typedef struct node
{
	int data;
	struct node*bro;//���ֵ�//
	struct node*kid;//����//
}TSBnode;
int treeheight(TSBnode *t)
{
	TSBnode *p;
	int m, max = 0;
	if (t == NULL)
		return 0;
	else if (t->kid == NULL)
		return 1;//û�к��ӽ�㷵��1//
	else
	{
		p = t->kid;//ָ���һ�����ӽ��//
		while (p != NULL)//�����к��ӽ�����ҳ�һ���߶����ĺ��ӽ��//
		{
			m = treeheight(p);
			if (max < m)
				max = m;
			p = p->bro;//�����������ֵܸ߶�//
		}
		return 1 + max;
	}
}