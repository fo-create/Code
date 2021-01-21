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
void level(Tree root)//层次遍历//
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
void allpath(Tree b)//逆向输出所有叶节点到根结点路径//
{
	struct snode
	{
		Tree node;//存放当前节点指针//
		int parent;//存放双亲在队列中的位置//
	}qu[MAX];//非环形队列//
	Tree q;
	int front, rear, p;
	front = rear = -1;
	rear++;
	qu[rear].node = b;//根结点进入队列//
	qu[rear].parent = -1;
	while (front != rear)
	{
		front++;
		q = qu[front].node;
		if (q->left == NULL && q->right == NULL)//q为叶节点时//
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
	x = findnode(root,val);//???怎么输入
	printf("%c", x->data);
	clear(x);
	return 0;
}
//ABDH00I00E0J00CF00G00