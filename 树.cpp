#include<stdio.h>
#include<stdlib.h>
#define MAX 50
typedef struct tree
{
	char data;
	struct tree *left;
	struct tree *right;
}NODE,*Tree;
Tree creat()
{
	Tree root;
	char val;
	scanf("%c", &val);
	if (val == '0')
	{
		root = NULL;
	}
	else {
		root = (Tree)malloc(sizeof(NODE));
		root->data = val;
		root->left = creat();
		root->right = creat();
	}
	return root;
}
Tree findnode(Tree root, char data)
{
	Tree ptr;
	if (root == NULL)
		return NULL;
	else
	{
		if (root->data == data)
			return root;
		else
		{
			if (ptr = findnode(root->left, data))
				return ptr;
			else if (ptr = findnode(root->right, data))
				return ptr;
			else
				return NULL;
		}
	}
}
int depth(Tree root)
{
	int depleft,depright;
	if (root == NULL)
		return 0;
	else
	{
		depleft = depth(root->left);
		depright = depth(root->right);
		if (depleft >= depright)
		{
			return depleft + 1;
		}
		else
		{
			return depright + 1;
		}
	}
}
void clear(Tree treenode)
{
	if (treenode)
	{
		clear(treenode->left);
		clear(treenode->right);
		free(treenode);
		treenode = NULL;
	}
}
void pre(Tree root)
{
	if (root)
	{
		printf("%c ", root->data);
		pre(root->left);
		pre(root->right);
	}
}
void in(Tree root)
{
	if (root)
	{
		
		in(root->left);
		printf("%c ", root->data);
		in(root->right);
	}
}
void post(Tree root)
{
	if (root)
	{
		
		post(root->left);
		post(root->right);
		printf("%c ", root->data);
	}
}
void level(Tree root)//��α���//
{
	Tree p;
	Tree q[MAX];
	int head = 0, tail = 0;
	if (root)
	{
		tail = (tail + 1) % MAX;
		q[tail] = root;
	}
	while (head != tail)
	{
		head = (head + 1) % MAX;
		p = q[head];
		printf("%c ", p->data);
		if (p->left != NULL)
		{
			tail = (tail + 1) % MAX;
			q[tail] = p->left;
		}
		if (p->right != NULL)
		{
			tail = (tail + 1) % MAX;
			q[tail] = p->right;
		}
	}
}
void allpath(Tree b)//�����������Ҷ�ڵ㵽�����·��//
{
	struct snode
	{
		Tree node;//��ŵ�ǰ�ڵ�ָ��//
		int parent;//���˫���ڶ����е�λ��//
	}qu[MAX];//�ǻ��ζ���//
	Tree q;
	int front, rear, p;
	front = rear = -1;
	rear++;
	qu[rear].node = b;//�����������//
	qu[rear].parent = -1;
	while (front != rear)
	{
		front++;
		q = qu[front].node;
		if (q->left == NULL && q->right == NULL)//qΪҶ�ڵ�ʱ//
		{
			p = front;
			while (qu[p].parent != -1)
			{
				printf("%c->", qu[p].node->data);
				p = qu[p].parent;
			}
			printf("%c\n", qu[p].node->data);
		}
		if (q->left != NULL)
		{
			rear++;
			qu[rear].node = q->left;
			qu[rear].parent = front;
		}
		if (q->right != NULL)
		{
			rear++;
			qu[rear].node = q->right;
			qu[rear].parent = front;
		}
	}
}
int main()
{
	Tree root,x;
	int result;
	char val;
	root = creat();
	/*allpath(root);
	result = depth(root);
	printf("%d\n", result);
	pre(root);
	printf("\n");
	in(root);
	printf("\n");
	post(root);
	printf("\n");
	level(root);
	printf("\n");*/
	scanf("%c", &val);
	x = findnode(root,val);//???��ô����
	printf("%c", x->data);
	clear(x);
	return 0;
}
//ABDH00I00E0J00CF00G00