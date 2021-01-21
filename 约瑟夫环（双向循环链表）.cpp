#include<stdio.h>
#include<malloc.h>
typedef struct list
{
	int val;
	struct list *prev;
	struct list *next;
}linkedlist;
void josephus(linkedlist *&dlist, int n, int m,int o);//从第几个人开始数//
int main()
{
	linkedlist *dlist;
	dlist = (linkedlist*)malloc(sizeof(linkedlist));
	dlist->prev = dlist->next = dlist;
	int m, n,pos;
	scanf("%d%d%d", &n,&pos,&m);
	josephus(dlist,n, m,pos);
	return 0;
}
void josephus(linkedlist *&dlist,int n, int m,int pos)
{
	int i,j;
	linkedlist *curr,*p,*q;
	p = dlist;
	for (i = 1; i <= n; i++)
	{
		q= (linkedlist*)malloc(sizeof(linkedlist));
		q->val = i;
		q->prev = p;
		p->next = q;
		p = q;
	}
	p->next = dlist->next;
	dlist->next->prev = p;
	curr = dlist->next;
	for (i = pos; i < n; i++)
	{
		for (j = pos; j <= m - 1; j++)
		{
			curr = curr->next;
			if (curr == dlist)
				curr = curr->next;
		}
		printf("%d ", curr->val);
		curr = curr->next;
		//把删除结点的前后结点相连
		curr->prev->prev->next = curr;
		curr->prev = curr->prev->prev;
		/*free(curr->prev);
		curr->prev = NULL;*/
		if (curr == dlist)
			curr = curr->next;
	}
	printf("%d", curr->val);
	free(dlist);
	free(curr);
}