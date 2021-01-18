#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}BiTNode, *Bitree;
bool searchBST(Bitree T, int key, Bitree f, Bitree *p);
bool insertBST(Bitree &T, int key);
bool deleteBST(Bitree &T, int key);
bool Delete(Bitree &p);
void inout(Bitree T);
int main()
{
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	Bitree T = NULL;
	for (int i = 0; i < 10; i++)//建树成功//
	{
		insertBST(T, a[i]);
	}
	inout(T);
	deleteBST(T, 47);
	inout(T);
	system("pause");
	return 0;
}
//二叉排序树查找//
bool searchBST(Bitree T, int key, Bitree f, Bitree *p)//初始f=NULL//
{
	if (!T)//查找失败//
	{
		*p = f;
		return false;
	}
	else if (key == T->data)//GET!//
	{
		*p = T;
		return true;
	}
	else if (key < T->data)//比当前结点小，在左子树中查找//
		return searchBST(T->left, key, T, p);
	else  //在右子树查找//
		return searchBST(T->right, key, T, p);
}
//二叉排序树插入//
bool insertBST(Bitree &T, int key)
{
	Bitree p, s;
	if (!searchBST(T, key, NULL, &p))//查找失败，即树中不存在待插入结点，可以插入//
	{
		s = (Bitree)malloc(sizeof(BiTNode));
		s->data = key;
		s->left = s->right = NULL;
		if (!p)
			T = s;//插入为根结点//
		else if (key < p->data)
			p->left = s;
		else
			p->right = s;
		return true;
	}
	else
		return false;//树中已存在相同关键字结点//
}
//二叉排序树删除//
bool deleteBST(Bitree &T, int key)
{
	if (!T)
		return false;
	else
	{
		if (key == T->data)
			return Delete(T);
		else if (key < T->data)
			return deleteBST(T->left, key);
		else
			return deleteBST(T->right, key);
	}
}
/*删除结点三种情况
叶子结点
仅有左或右子树的结点
左右子树都有的结点
*/
bool Delete(Bitree &p)
{
	Bitree q, s;
	if (p->right == NULL)//右子树为空只需重接它的左子树//
	{
		q = p;
		p = p->left;
		free(q);
		q = NULL;
	}
	else if (p->left == NULL)//只需重接右子树//
	{
		q = p;
		p = p->right;
		free(q);
		q = NULL;
	}
	else//左右子树均不空//
	{
		q = p;
		s = p->left;
		while (s->right)//转左，然后向右到尽头（找到待删节点的前驱//
		{
			q = s;
			s = s->right;
		}
		p->data = s->data;//s指向的是被删节点的直接前驱//
		if (q != p)
			q->right = s->left;
		else
			q->left = s->left;
		free(s);
		s = NULL;
	}
	return true;
}
//中序输出//
void inout(Bitree T)
{
	if (T == NULL)
		return;
	else
	{
		inout(T->left);
		printf("%d ", T->data);
		inout(T->right);
	}
}
