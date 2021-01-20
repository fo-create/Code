#include<stdio.h>
#include<stdlib.h>
#define MAX 50
typedef struct
{
	int front;
	int rear;
	int data[MAX];
}SqQueue;
SqQueue *init()
{
	SqQueue *q;
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = 0;
	q->rear = 0;
	return q;
}
int Queuelength(SqQueue *s)
{
	return (s->rear - s->front + MAX) % MAX;
}
void EnQueue(SqQueue* s, int data)//进队
{
	if ((s->rear+1)%MAX==s->front)
		return;
	s->data[s->rear] = data;
	s->rear = (s->rear + 1) % MAX;
}
void DeQueue(SqQueue *s)//出队
{
	if (s->front == s->rear)
		return;
	printf("%d\n", s->data[s->front]);
	s->front = (s->front + 1) % MAX;
}
int main()
{
	SqQueue *s;
	int val;
	s = init();
	for (int i = 0; i < 5; i++) {
		scanf("%d", &val);
		EnQueue(s, val);
	}
	while (!(s->front==s->rear))
		DeQueue(s);
}