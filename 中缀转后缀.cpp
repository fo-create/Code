#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define MAX 1000
typedef struct
{
	int top;
	char data[MAX];
}sqstacks;
int main()
{
	sqstacks *p, *q;
	p = (sqstacks *)malloc(sizeof(sqstacks));
	p->top = 0;
	q = (sqstacks *)malloc(sizeof(sqstacks));
	q->top = 0;
	char data[MAX];
	scanf("%s", data);
	int length = strlen(data);
	for (int i = 0; i < length; i++)
	{
		if (data[i] >= 'a'&&data[i] <= 'z')
			p->data[++p->top] = data[i];
		else if (data[i] == '+' || data[i] == '-')
		{
			if (q->top == 0)
				q->data[++q->top] = data[i];
			else
			{
				while (q->data[q->top] == '+'|| q->data[q->top] == '-' || q->data[q->top] == '*' || q->data[q->top] == '/')
				{
					p->data[++p->top] = q->data[q->top--];
				}
				q->data[++q->top] = data[i];
			}
		}
		else if (data[i] == '*' || data[i] == '/')
		{
			if (q->top == 0)
				q->data[++q->top] = data[i];
			else
			{
				while (q->data[q->top] == '*' || q->data[q->top] == '/')
				{
					p->data[++p->top] = q->data[q->top--];
				}
				q->data[++q->top] = data[i];
			}
		}
		else if (data[i] == '(')
		{
			q->data[++q->top] = data[i];
		}
		else if (data[i] == ')')
		{
			while (q->data[q->top] != '(')
			{
				p->data[++p->top] = q->data[q->top--];
			}
			q->data[q->top--];
		}
	}
	while (q->top != 0)
	{
		p->data[++p->top] = q->data[q->top--];
	}
	for (int i = 1; i<length; i++)
	{
		printf("%c", p->data[i]);
	}
	return 0;
}