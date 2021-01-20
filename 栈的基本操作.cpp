//#include<stdio.h>
//#include<stdlib.h>
//#define MAX 50
//typedef struct stack
//{
//	int data[MAX];
//	int top;
//}stacktype;
//stacktype *init()
//{
//	stacktype* p;
//	p = (stacktype*)malloc(sizeof(stacktype));
//	p->top = -1;
//	return p;
//}
//int isempty(stacktype *s)
//{
//	return s->top == -1;
//}
//int isfull(stacktype *s)
//{
//	return s->top = MAX;
//}
//void clear(stacktype *s)
//{
//	s->top = -1;
//}
//void push(stacktype* s,int data)
//{
//	if (s->top== MAX-1)
//		return;
//	s->data[++(s->top)] = data;
//}
//void pop(stacktype *s)
//{
//	if (s->top == -1)
//		return;
//	else
//	printf("%d ", s->data[s->top--]);
//}
//int main()
//{
//	stacktype *s;
//	int val;
//	s=init();
//	for (int i = 0; i < 5; i++)
//	{
//		scanf("%d", &val);
//		push(s, val);
//	}
//	while(!isempty(s))
//		pop(s);
//	return 0;
//}