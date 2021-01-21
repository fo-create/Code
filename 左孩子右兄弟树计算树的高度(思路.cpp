#include<cstdio>
typedef struct node
{
	int data;
	struct node*bro;//右兄弟//
	struct node*kid;//左孩子//
}TSBnode;
int treeheight(TSBnode *t)
{
	TSBnode *p;
	int m, max = 0;
	if (t == NULL)
		return 0;
	else if (t->kid == NULL)
		return 1;//没有孩子结点返回1//
	else
	{
		p = t->kid;//指向第一个孩子结点//
		while (p != NULL)//从所有孩子结点中找出一个高度最大的孩子结点//
		{
			m = treeheight(p);
			if (max < m)
				max = m;
			p = p->bro;//继续求其他兄弟高度//
		}
		return 1 + max;
	}
}