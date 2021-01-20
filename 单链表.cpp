#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef struct node
{
	int data;
	struct node *next;
}Node,*linkedlist;
void headcreate(linkedlist &head);
void endcreate(linkedlist &head);
void outlist(linkedlist head);
void insertkey(linkedlist &head, int key1, int key2, int pos);
void dellist(linkedlist &head, int key);
void bubblelist(linkedlist &head);
int main()
{
	linkedlist head;
	head = (linkedlist)malloc(sizeof(Node));
	head->next = NULL;
	/*headcreate(head);
	insertkey(head, 666, 999, 6);
	dellist(head, 3);*/
	endcreate(head);
	bubblelist(head);
	outlist(head);
	return 0;
}
/*
单链表的创建
*/
void headcreate(linkedlist &head)//头插法
{
	int a[N] = { 1,2,3,4,5,6,7,8,9,10 };
	linkedlist p;
	for (int i = 0; i < N; i++)
	{	
		p= (linkedlist)malloc(sizeof(Node));
		p->data = a[i];
		p->next = head->next;
		head->next = p;
	}
}
void endcreate(linkedlist &head)//尾插法
{
	int a[N] = { 1,2,3,4,5,6,7,8,9,10 };
	linkedlist p,q;
	q = head;
	for (int i = 0; i < N; i++)
	{
		p = (linkedlist)malloc(sizeof(Node));
		p->data = a[i];
		q->next = p;
		q = p;
	}
	q->next = NULL;
}
/*
单链表的输出
*/
void outlist(linkedlist head)
{
	linkedlist p;
	p = head->next;
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}
/*
单链表的插入
*/
void insertkey(linkedlist &head, int key1,int key2, int pos)//在位置pos之后/之前插入key结点
{
	linkedlist p, q, s1,s2;
	int cnt = 1;
	s1 = (linkedlist)malloc(sizeof(Node));
	s1->data = key1;
	s2 = (linkedlist)malloc(sizeof(Node));
	s2->data = key2;
	q = head;
	p = head->next;
	while (p != NULL&&cnt<pos)
	{
		q = p;//q始终为p的前驱结点
		p = p->next;
		cnt++;
	}
	//在结点后插入结点
	s1->next = p->next;
	p->next = s1;
	//在结点前插入结点
	s2->next = p;
	q->next = s2;
}
//单链表删除结点
void dellist(linkedlist &head, int key)
{
	linkedlist p, q;
	q = head;
	p = head->next;
	while (p->data != key)
	{
		q = p;
		p = p->next;
	}
	q->next = p->next;
	/*free(p);*/
}
void bubblelist(linkedlist &head)
{
	linkedlist cur, pre,temp,last=NULL;//last为未排序的最后一个元素
	temp = head;
	while (last != head->next) {
		pre = cur = head->next;
		while (cur != last)
		{
			if (pre->data < cur->data)
			{
				temp->data = pre->data;
				pre->data = cur->data;
				cur->data = temp->data;
			}
			pre = cur;
			cur = cur->next;
		}
		last = pre;
	}
}