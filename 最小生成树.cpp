#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
#define max 100
#define INF 32767
typedef struct
{
	int edges[max][max];
	int n, e;//顶点数，边数//
}MGraph;
typedef struct
{
	int head;//边的起始顶点//
	int tail;//边的终止顶点//
	int weight;//权值//
}edge;
typedef struct
{
	int rank;//结点的秩//
	int parent;//结点的双亲//
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
	for (i = 0; i < n; i++)//顶点编号为0到n-1//
	{
		t[i].rank = 0;
		t[i].parent = i;//双亲初始化指向自己//
	}
}
int find(UFSTree t[], int x)
{
	if (x != t[x].parent)
		return (find(t, t[x].parent));//双亲不是自己，递归查找//
	else
		return x;
}
void Union(UFSTree t[], int x, int y)
{
	x = find(t, x);
	y = find(t, y);
	if (t[x].rank > t[y].rank)
		t[y].parent = x;//y的秩<=x，则将y连到x上//
	else
	{
		t[x].parent = y;
		if (t[x].rank == t[y].rank)
			t[y].rank++;
	}
}
void Prim(MGraph g, int v)//带权无向图适用//
{
	int lowcost[max], closest[max];
	edge E[max];
	int min, i, j, k, cnt;
	for (i = 0; i < g.n; i++)//赋初值//
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	//closest[v] = -1;//顶点v进入//
	//cnt = 1;//边计数器//
	for (i = 1; i < g.n; i++)//找n-1个顶点//
	{
		min = INF;
		/*k = 0;*/
		for (j = 0; j < g.n; j++)//在V-U中找出离U最近的顶点k//
			/*if(closest[j]!=-1&& lowcost[j] < min)*/
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;//k记录最近顶点的编号//
			}
		printf("边(%d,%d)权为:%d\n", closest[k], k, min);
		/*if (k != 0)
		{
			E[cnt].head = closest[k];
			E[cnt].tail = k;
			E[cnt].weight = lowcost[closest[k]];
			cnt++;
		}*/
		lowcost[k] = 0;//标记k进入U//
		/*closest[k] = -1;*/
		for (j = 0; j < g.n; j++)//修改两数组//
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
		vest[i] = i;//辅助数组初始化//
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
	insert(E, 2 * G->e);/*对E数组按权值递增排序*/
	k = 1;//k表示当前构造树的第几条边，初值1//
	j = 0;//j表示E中边的下标，初值为0//
	while (k < G->n)//生成边数小于n//
	{
		u1 = E[j].head;//取一条边的头尾顶点//
		v1 = E[j].tail;
		sn1 = vest[u1];
		sn2 = vest[v1];//得到两点所属集合编号//
		if (sn1 != sn2)//不同集合，故是一条边//
		{
			printf("(%d,%d):%d\n", u1, v1, E[j].weight);
			k++;//边数增加//
			for (i = 0; i < G->n; i++)
				if (vest[i] == sn2)//两集合统一编号//
					vest[i] = sn1;
		}
		j++;//扫描下一条边//
	}
}
void Kruskal_2(MGraph *G)
{
	int i, j, u1, v1, sn1, sn2, k;
	UFSTree t[max];
	edge E[max];//存放所有边//
	k = 0;//E数组下标从0开始//
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
	insert(E, 2 * G->e);/*对E数组按权值递增排序*/
	make_set(t, G->n);//初始化并查集树//
	k = 1;//k表示当前构造树的第几条边，初值1//
	j = 0;//j表示E中边的下标，初值为0//
	while (k < G->n)//生成边数小于n//
	{
		u1 = E[j].head;//取一条边的头尾顶点//
		v1 = E[j].tail;
		sn1 = find(t, u1);
		sn2 =find(t,v1);//得到两点所属集合编号//
		if (sn1 != sn2)//不同集合，故是一条边//
		{
			printf("(%d,%d):%d\n", u1, v1, E[j].weight);
			k++;//边数增加//
			Union(t, u1, v1);
		}
		j++;//扫描下一条边//
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
	printf("Kruskal并查集实现:\n");
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