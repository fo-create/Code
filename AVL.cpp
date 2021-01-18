#include<stdio.h>
#include<stdlib.h>
#define LH 1//���//
#define EH 0//�ȸ�//
#define RH -1//�Ҹ�//
typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	int bf;//ƽ������//
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
//����pΪ���Ķ�����������������//
//�����pָ���µ�������㣬����ת����ǰ���������ĸ����//
void RRotate(Bitree &p)
{
	Bitree L;
	L = p->left;//Lָ��p�������������//
	p->left = L->right;//L���������ҽ�Ϊp��������//
	L->right = p;
	p = L;//pָ���µĸ����//
}
//��������//
void LRotate(Bitree &p)
{
	Bitree R;
	R = p->right;//Rָ��p�������������//
	p->right = R->left;//R���������ҽ�Ϊp��������//
	R->left = p;
	p = R;//ָ������//
}
//��ƽ����ת����˫��ת)������Tָ���µĸ����//
void Leftbalance(Bitree &T)
{
	Bitree L, Lr;
	L = T->left;//ָ��T�����������//
	switch (L->bf)//���T��������ƽ��ȣ�����Ӧ����//
	{
	case LH://�������ߣ����½ڵ������T�����ӵ��������ϣ�����С��ƽ�������е���������//
		T->bf = L->bf = EH;//ת��ƽ��bfΪ0//
		RRotate(T);
		break;
	case RH://���������ӵ��������ϣ�˫������//
		Lr = L->right;//���ӵ���������//
		switch (Lr->bf)//�޸�T�������ӵ�ƽ������//					   
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
		LRotate(T->left);//��T��������������������//
		RRotate(T);//��T������������//
	}
}
//��ƽ����ת����˫��ת)������Tָ���µĸ����//
void RightBalance(Bitree &T)
{
	Bitree R, Rl;
	R = T->right;//ָ��T�������������//
	switch (R->bf)
	{
	case RH://ֻ�赥����//
		T->bf = R->bf = EH;
		LRotate(T);
		break;
	case LH://��ʱ��Ҫ˫��//
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
bool InsertAVL(Bitree &T, int e, bool *taller)//�½ڵ�e��taller��ӳT�������//
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
		{//��������������//
			if (!InsertAVL(T->left, e, taller))
				return false;
			if (taller)//�Ѿ����뵽������������������//
			{
				switch (T->bf)//���T��ƽ���//
				{
				case LH://ԭ���������ߣ���ƽ�⴦��//
					Leftbalance(T);
					*taller = false;
					break;
				case EH://ԭ���ȸ�//
					T->bf = LH;
					*taller = true;
					break;
				case RH://ԭ����������//
					T->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else//��������������//
		{
			if (!InsertAVL(T->right, e, taller))//δ����//
				return false;
			if (taller)//�Ѿ����뵽������������������//
			{
				switch (T->bf)//���T��ƽ���//
				{
				case LH://ԭ���������ߣ���ƽ�⴦��//
					T->bf = EH;
					*taller = false;
					break;
				case EH://ԭ���ȸ�//
					T->bf = RH;
					*taller = true;
					break;
				case RH://ԭ����������//
					RightBalance(T);
					*taller = false;
					break;
				}
			}
		}
	}
	return true;
}
//�������//
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

