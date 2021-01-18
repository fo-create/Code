#include<stdio.h>
#include<stdlib.h>
#define LH 1//左高//
#define EH 0//等高//
#define RH -1//右高//
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	int bf;//平衡因子//
}BiTNode, *Bitree;
void inout(Bitree T);
void RRotate(Bitree &p);
void LRotate(Bitree &p);
void Leftbalance(Bitree &T);
void RightBalance(Bitree &T);
bool InsertAVL(Bitree &T, int e, bool *taller);
int main()
{
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	Bitree T = NULL;
	bool taller;
	for (int i = 0; i < 10; i++)
	{
		InsertAVL(T, a[i], &taller);
	}
	inout(T);
	system("pause");
	return 0;
}
//对以p为根的二叉排序树右旋处理//
//处理后p指向新的树根结点，即旋转处理前的左子树的根结点//
void RRotate(Bitree &p)
{
	Bitree L;
	L = p->left;//L指向p的左子树根结点//
	p->left = L->right;//L的右子树挂接为p的左子树//
	L->right = p;
	p = L;//p指向新的根结点//
}
//左旋处理//
void LRotate(Bitree &p)
{
	Bitree R;
	R = p->right;//R指向p的右子树根结点//
	p->right = R->left;//R的左子树挂接为p的右子树//
	R->left = p;
	p = R;//指向根结点//
}
//左平衡旋转处理（双旋转)处理完T指向新的根结点//
void Leftbalance(Bitree &T)
{
	Bitree L, Lr;
	L = T->left;//指向T左子树根结点//
	switch (L->bf)//检查T左子树的平衡度，做相应处理//
	{
	case LH://左子树高，即新节点插在了T的左孩子的左子树上，对最小不平衡树进行单右旋处理//
		T->bf = L->bf = EH;//转完平衡bf为0//
		RRotate(T);
		break;
	case RH://插在了左孩子的右子树上，双旋处理//
		Lr = L->right;//左孩子的右子树根//
		switch (Lr->bf)//修改T及其左孩子的平衡因子//					   
		{
		case LH:
			T->bf = RH;
			L->bf = EH;
			break;
		case EH:
			T->bf = L->bf = EH;
			break;
		case RH:
			T->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		LRotate(T->left);//对T的左子树进行左旋处理//
		RRotate(T);//对T进行右旋处理//
	}
}
//右平衡旋转处理（双旋转)处理完T指向新的根结点//
void RightBalance(Bitree &T)
{
	Bitree R, Rl;
	R = T->right;//指向T的右子树根结点//
	switch (R->bf)
	{
	case RH://只需单左旋//
		T->bf = R->bf = EH;
		LRotate(T);
		break;
	case LH://此时需要双旋//
		Rl = R->left;
		switch (Rl->bf)
		{
		case RH:
			T->bf = LH;
			R->bf = EH;
			break;
		case EH:
			T->bf = R->bf = EH;
			break;
		case LH:
			T->bf = EH;
			R->bf = RH;
			break;
		}
		Rl->bf = EH;
		RRotate(T->right);
		LRotate(T);
	}
}
bool InsertAVL(Bitree &T, int e, bool *taller)//新节点e，taller反映T长高与否//
{
	if (!T)
	{
		T = (Bitree)malloc(sizeof(BiTNode));
		T->data = e;
		T->left = T->right = NULL;
		T->bf = EH;
		*taller = true;
	}
	else
	{
		if (e == T->data)
		{
			*taller = false;
			return false;
		}
		if (e < T->data)
		{//在左子树中搜索//
			if (!InsertAVL(T->left, e, taller))
				return false;
			if (taller)//已经插入到左子树，左子树长高//
			{
				switch (T->bf)//检查T的平衡度//
				{
				case LH://原来左子树高，左平衡处理//
					Leftbalance(T);
					*taller = false;
					break;
				case EH://原来等高//
					T->bf = LH;
					*taller = true;
					break;
				case RH://原来右子树高//
					T->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else//在右子树中搜索//
		{
			if (!InsertAVL(T->right, e, taller))//未插入//
				return false;
			if (taller)//已经插入到右子树，右子树长高//
			{
				switch (T->bf)//检查T的平衡度//
				{
				case LH://原来左子树高，左平衡处理//
					T->bf = EH;
					*taller = false;
					break;
				case EH://原来等高//
					T->bf = RH;
					*taller = true;
					break;
				case RH://原来右子树高//
					RightBalance(T);
					*taller = false;
					break;
				}
			}
		}
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

