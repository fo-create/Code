#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
#define max 100
#define INF 32767
typedef struct
{
	int edges[max][max];
	int n, e;//������������//
}MGraph;
typedef struct
{
	int head;//�ߵ���ʼ����//
	int tail;//�ߵ���ֹ����//
	int weight;//Ȩֵ//
}edge;
typedef struct
{
	int rank;//������//
	int parent;//����˫��//
}UFSTree;
void create(MGraph *g)
{
	int i, j, k, weight;
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			if (i == j)
				g->edges[i][j] = 0;
			else
				g->edges[i][j] = INF;
		}
	}
	for (k = 0; k < g->e; k++)
	{
		scanf("%d %d %d", &i, &j, &weight);
		g->edges[i][j] = weight;
		g->edges[j][i] = weight;
	}
}
void insert(edge a[],int N)
{
	for (int i = 1; i < N; i++)
	{
		int j = i - 1;
		edge temp = a[i];
		while (j >= 0 && temp.weight < a[j].weight)
		{
			a[j + 1] = a[j--];
		}
		a[j + 1]= temp;
	}
}
void make_set(UFSTree t[], int n)
{
	int i;
	for (i = 0; i < n; i++)//������Ϊ0��n-1//
	{
		t[i].rank = 0;
		t[i].parent = i;//˫�׳�ʼ��ָ���Լ�//
	}
}
int find(UFSTree t[], int x)
{
	if (x != t[x].parent)
		return (find(t, t[x].parent));//˫�ײ����Լ����ݹ����//
	else
		return x;
}
void Union(UFSTree t[], int x, int y)
{
	x = find(t, x);
	y = find(t, y);
	if (t[x].rank > t[y].rank)
		t[y].parent = x;//y����<=x����y����x��//
	else
	{
		t[x].parent = y;
		if (t[x].rank == t[y].rank)
			t[y].rank++;
	}
}
void Prim(MGraph g, int v)//��Ȩ����ͼ����//
{
	int lowcost[max], closest[max];
	edge E[max];
	int min, i, j, k, cnt;
	for (i = 0; i < g.n; i++)//����ֵ//
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	//closest[v] = -1;//����v����//
	//cnt = 1;//�߼�����//
	for (i = 1; i < g.n; i++)//��n-1������//
	{
		min = INF;
		/*k = 0;*/
		for (j = 0; j < g.n; j++)//��V-U���ҳ���U����Ķ���k//
			/*if(closest[j]!=-1&& lowcost[j] < min)*/
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;//k��¼�������ı��//
			}
		printf("��(%d,%d)ȨΪ:%d\n", closest[k], k, min);
		/*if (k != 0)
		{
			E[cnt].head = closest[k];
			E[cnt].tail = k;
			E[cnt].weight = lowcost[closest[k]];
			cnt++;
		}*/
		lowcost[k] = 0;//���k����U//
		/*closest[k] = -1;*/
		for (j = 0; j < g.n; j++)//�޸�������//
			/*if(closest[j]!=-1&& g.edges[k][j] < lowcost[j])*/
			if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.edges[k][j];
				closest[j] = k;
			}
	}
}
void Kruskal_1(MGraph *G)
{
	int i, j, u1, v1, sn1, sn2, k;
	int vest[max];
	edge E[max];
	for (i = 0; i < G->n; i++)
		vest[i] = i;//���������ʼ��//
	k = 0;
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] != 0 && G->edges[i][j] != INF)
			{
				E[k].head = i; E[k].tail = j; E[k].weight = G->edges[i][j];
				k++;
			}
		}
	}
	insert(E, 2 * G->e);/*��E���鰴Ȩֵ��������*/
	k = 1;//k��ʾ��ǰ�������ĵڼ����ߣ���ֵ1//
	j = 0;//j��ʾE�бߵ��±꣬��ֵΪ0//
	while (k < G->n)//���ɱ���С��n//
	{
		u1 = E[j].head;//ȡһ���ߵ�ͷβ����//
		v1 = E[j].tail;
		sn1 = vest[u1];
		sn2 = vest[v1];//�õ������������ϱ��//
		if (sn1 != sn2)//��ͬ���ϣ�����һ����//
		{
			printf("(%d,%d):%d\n", u1, v1, E[j].weight);
			k++;//��������//
			for (i = 0; i < G->n; i++)
				if (vest[i] == sn2)//������ͳһ���//
					vest[i] = sn1;
		}
		j++;//ɨ����һ����//
	}
}
void Kruskal_2(MGraph *G)
{
	int i, j, u1, v1, sn1, sn2, k;
	UFSTree t[max];
	edge E[max];//������б�//
	k = 0;//E�����±��0��ʼ//
	for (i = 0; i < G->n; i++)
	{
		for (j = 0; j < G->n; j++)
		{
			if (G->edges[i][j] != 0 && G->edges[i][j] != INF)
			{
				E[k].head = i; E[k].tail = j; E[k].weight = G->edges[i][j];
				k++;
			}
		}
	}
	insert(E, 2 * G->e);/*��E���鰴Ȩֵ��������*/
	make_set(t, G->n);//��ʼ�����鼯��//
	k = 1;//k��ʾ��ǰ�������ĵڼ����ߣ���ֵ1//
	j = 0;//j��ʾE�бߵ��±꣬��ֵΪ0//
	while (k < G->n)//���ɱ���С��n//
	{
		u1 = E[j].head;//ȡһ���ߵ�ͷβ����//
		v1 = E[j].tail;
		sn1 = find(t, u1);
		sn2 =find(t,v1);//�õ������������ϱ��//
		if (sn1 != sn2)//��ͬ���ϣ�����һ����//
		{
			printf("(%d,%d):%d\n", u1, v1, E[j].weight);
			k++;//��������//
			Union(t, u1, v1);
		}
		j++;//ɨ����һ����//
	}
}
int main()
{
	MGraph *G=new MGraph;
	scanf("%d%d", &G->n, &G->e);
	create(G);
	printf("Prim:\n");
	Prim(*G, 0);
	printf("Kruskal:\n");
	Kruskal_1(G);
	printf("Kruskal���鼯ʵ��:\n");
	Kruskal_2(G);
	return 0;
}
//6 10
//0 1 6
//0 3 5
//0 2 1
//1 2 5
//2 3 5
//1 4 3
//4 5 6
//5 3 2
//2 4 6
//2 5 4