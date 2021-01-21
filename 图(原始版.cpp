#include<iostream>
#define max 100
#define INF 0x3f3f3f3f
using namespace std;
int visited[100];//标志数组//
bool has;
typedef struct EdgeNode {
	int adjvex;//顶点i相邻的顶点编号//
	struct EdgeNode *next;//下一个边结点指针域//
	int weight;
}edgeNode;//边结点类型//
typedef struct VertexNode
{
	char data;//顶点信息//
	int count;//存放顶点入度//
	edgeNode *firstedge;//指向第一个边结点//
}VertexNode,AdjList[100];//临界表头结点类型,AdjList是邻接表类型（100-结点数量）//
typedef struct {
	AdjList adjList;//邻接表//
	int numVertexes, numEdges;//顶点数，边数//
}GraphAdjList;
typedef struct
{
	int data;
	int parent;

}QUERE;
//邻接矩阵结构体//
typedef struct
{
	int no;//顶点编号//
	//其他信息//
}VertexType;
typedef struct
{
	int edges[max][max];
	int n, e;//顶点数，边数//
	VertexType vexs[max];
}MGraph;
class AdjacencyList {
public:
	void CreateALGraph(GraphAdjList *G);//无向图邻接表的创建//
	void createALGraph(GraphAdjList *G);//有向图邻接表的创建//
	int locate(GraphAdjList *G, int v);
	void ShowALGraph(GraphAdjList *G);
	void DFS(GraphAdjList *G, int i);
	void DFSTraverse(GraphAdjList *G);
	void BFS(GraphAdjList *G, int v);
	void BFSTraverse(GraphAdjList *G);
	void existpath(GraphAdjList *G, int u, int v, bool &has);
	void shortpath(GraphAdjList *G, int u, int v);
	void Dijkstra(MGraph G, int v);
	void Dispath(MGraph g, int dist[], int path[], int S[], int v);
	void Floyd(MGraph g);
	void Dispath(MGraph g, int A[][max], int path[][max]);
	void TopSort(GraphAdjList *G);
	void CriticalPath(GraphAdjList *G);
};
//无向图邻接表创建//
void AdjacencyList::CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	edgeNode *e;
	cin >> G->numVertexes >> G->numEdges;//输入顶点数和边数//
	//读入顶点信息，建立顶点表//
	for (i = 0; i < G->numVertexes; i++)
	{
		cin >> G->adjList[i].data;//输入顶点信息//
		G->adjList[i].firstedge = NULL;//边表置为空表//
	}
	for (k = 0; k < G->numEdges; k++)
	{
		cin >> i >> j;//输入边上的顶点序号//
		e = new EdgeNode;
		e->adjvex = j;
		e->next = G->adjList[i].firstedge;
		G->adjList[i].firstedge = e;
		e = new EdgeNode;
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}
//有向图邻接表创建//
void AdjacencyList::createALGraph(GraphAdjList *G)
{
	int i, j, k, weight;
	int x, y;//弧头，弧尾顶点//
	edgeNode *e;
	scanf("%d%d", &G->numVertexes, &G->numEdges);//输入顶点数和边数//
	//读入顶点信息，建立顶点表//
	for (i =0 ;i <G->numVertexes; i++)
	{
		G->adjList[i].data = i;
		G->adjList[i].firstedge = NULL;//边表置为空表//
	}
	for (k = 0; k < G->numEdges; k++)
	{
		scanf("%d%d%d", &i, &j,&weight);//输入边上的顶点序号//
		x = locate(G, i);
		y = locate(G, j);
		e = (edgeNode*)malloc(sizeof(edgeNode));
		e->weight = weight;
		e->adjvex = y;
		e->next = G->adjList[x].firstedge;
		G->adjList[x].firstedge = e;
	}
}
int AdjacencyList::locate(GraphAdjList *G, int v)//查找顶点在顺序表中位置//
{
	for (int i = 0; i < G->numVertexes; i++)
	{
		if (G->adjList[i].data == v)
			return i;
	}
	return 0;
}
void AdjacencyList::ShowALGraph(GraphAdjList *G)
{
	for (int i = 0; i < G->numVertexes; i++)
	{
		cout << "顶点" << i << ":" << G->adjList[i].data << "--firstedge--";
		edgeNode *p = new edgeNode;
		p = G->adjList[i].firstedge;
		while (p)
		{
			cout << p->adjvex << "--next--";
			p = p->next;
		}
		cout << "--NULL" << endl;
	}
}
void AdjacencyList::DFS(GraphAdjList *G, int i)
{
	EdgeNode *p;//以i为起始点用邻接表进行dfs搜索//
	visited[i] = 1;//访问并做标记//
	cout << G->adjList[i].data << "--";
	p = G->adjList[i].firstedge;//p指向顶点i的第一个邻接点//
	while (p)
	{
		if (!visited[p->adjvex])
		{
			DFS(G, p->adjvex);//递归返回//
		}
		p = p->next;//找下一个邻接点//
	}
}
void AdjacencyList::DFSTraverse(GraphAdjList *G)
{
	for (int i = 0; i < G->numVertexes; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->numVertexes; i++)
	{
		if (visited[i] == 0)
		{
			DFS(G, i);
		}
	}
}
void AdjacencyList::BFS(GraphAdjList *G, int v)
{
	edgeNode *p;
	int queue[100], front = 0, rear = 0;
	int w, i;
	for (i = 0; i < G->numVertexes; i++)
	{
		visited[i] = 0;//标志数组初始化//
	}
	printf("%2d", v);//输出访问结点编号//
	visited[v] = 1;
	rear = (rear + 1) % 100;
	queue[rear] = v;//v进队//
	while (front != rear)//队列不为空，循环//
	{
		front = (front + 1) % 100;
		w = queue[front];//出队赋给w//
		p = G->adjList[w].firstedge;
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)//当前邻接节点未访问//
			{
				printf("%2d", p->adjvex);//访问邻接节点//
				visited[p->adjvex] = 1;
				rear = (rear + 1) % 100;
				queue[rear] = p->adjvex;//该顶点进队//
			}
			p = p->next;
		}
	}
	printf("\n");
}
void AdjacencyList::BFSTraverse(GraphAdjList *G)
{
	for (int i = 0; i < G->numVertexes; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < G->numVertexes; i++)
	{
		if (visited[i] == 0)
		{
			BFS(G, i);
		}
	}
}
void AdjacencyList::existpath(GraphAdjList *G, int u, int v, bool &has)//has判断u-v是否有路径//
{
	int w;
	edgeNode *p;
	visited[u] = 1;
	if (u == v)
	{
		has = true;
		return;
	}
	p = G->adjList[u].firstedge;//指向u的第一个相邻结点//
	while (p != NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			existpath(G, w, v, has);
		p = p->next;
	}
}
void AdjacencyList::shortpath(GraphAdjList *G, int u, int v)
{
	edgeNode *p;
	int w, i;
	QUERE qu[100];
	int front = -1, rear = -1;
	int visited[100];
	for (i = 0; i < G->numVertexes; i++)
		visited[i] = 0;
	rear++;//顶点u进队//
	qu[rear].data = u;
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear)
	{
		front++;
		w = qu[front].data;//出队//
		if (w == v)//找到v时输出路径之逆并退出//
		{
			i = front;
			while (qu[i].parent != -1)
			{
				printf("%2d", qu[i].data);
				i = qu[i].parent;//往前走//
			}
			printf("%2d\n", qu[i].data);
			break;
		}
		p = G->adjList[w].firstedge;//找w的第一个邻接点//
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)
			{
				visited[p->adjvex] = 1;
				rear++;
				qu[rear].data = p->adjvex;
				qu[rear].parent = front;
			}
			p = p->next;
		}
	}
}
void AdjacencyList::Dijkstra(MGraph g, int v)
{
	int dist[max];//保存从源点v到顶点i的目前最短路径长度，初值为权值，可能被更新大小//
	int path[max];//保存当前最短路径中前一个顶点的编号//
	int s[max];//0-未找到源点到i的最短路径;1-找到//
	int mindis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];
		s[i] = 0;
		if (g.edges[v][i] < INF)//???//
			path[i] = v;//若v到i有边，置i的前一个顶点为v???//
		else
			path[i] = -1;
	}
	s[v] = 1;//编号v操作完成//
	path[v] = 0;
	for (i = 0; i < g.n; i++)//循环直到所有顶点的最短路径都求出//
	{
		mindis = INF;
		for(j=0;j<g.n;j++)
			if (s[j] == 0 && dist[j] < mindis)//选取不在s中且具有最小距离的顶点u//
			{
				u = j;
				mindis = dist[j];
			}
		s[u] = 1;
		for(j=0;j<g.n;j++)
			if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])//修改不在s中顶点的距离//
			{
				dist[j] = dist[u] + g.edges[u][j];
				path[j] = u;
			}
	}
	Dispath(g, dist, path, s, v);//输出最短路径//
}
void AdjacencyList::Dispath(MGraph g, int dist[], int path[], int S[], int v)
{
	int i, j, k;
	int apath[max], d;//存放一条最短路径（逆向）及其顶点个数//
	for(i=0;i<g.n;i++)//循环输出v到i的路径//
		if (S[i] == 1 && i != v)
		{
			printf("%d-%d:%d", v, i, dist[i]);
			d = 0; apath[d] = i;
			k = path[i];
			if (k == -1)
				printf("无路径\n");
			else
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d]=i;//添加路径上的起点???//
				printf("%d", apath[d]);
				for (j = d - 1; j >= 0; j--)
					printf("-%d", apath[j]);
				printf("\n");
			}
		}
}
void AdjacencyList:: Floyd(MGraph g)
{
	int A[max][max], path[max][max];
	int i, j, k;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;//i到j有边时//
			else
				path[i][j] = -1;
		}
	for (k = 0; k < g.n; k++)
	{
		for (i = 0; i < g.n; i++)
			for (j = 0; j < g.n; j++)
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
	}
	Dispath(g, A, path);
}
void AdjacencyList::Dispath(MGraph g, int A[][max], int path[][max])
{
	int i, j, k, s;
	int apath[max], d;
	for(i=0;i<g.n;i++)
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)//若存在路径//
			{
				printf("%d-%d", i, j);
				k = path[i][j];
				d = 0; apath[d] = j;//路径上添加终点//
				while (k != -1 && k != i)//添加中间点//
				{
					d++;
					apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;
				printf("%d", apath[d]);
				for (s = d - 1; s >= 0; s--)
				{
					printf("%2d", apath[s]);
				}
				printf("路径长度为：%d", A[i][j]);
			}
		}
} 
void AdjacencyList::TopSort(GraphAdjList *G)
{
	int i, j;
	int st[max], top = -1;
	edgeNode *p;
	for (i = 0; i < G->numVertexes; i++)
		G->adjList[i].count = 0;
	for (i = 0; i < G->numVertexes; i++)//求所有顶点的入度//
	{
		p = G->adjList[i].firstedge;
		while (p != NULL)
		{
			G->adjList[p->adjvex].count++;
			p = p->next;
		}
	}
	for(i=0;i<G->numVertexes;i++)
		if (G->adjList[i].count == 0)
		{
			st[++top] = i;//入度为0顶点进栈//
		}
	while (top > -1)//栈非空循环//
	{
		i = st[top--];
		printf("%d", i);
		p = G->adjList[i].firstedge;
		while (p != NULL)
		{
			j = p->adjvex;
			G->adjList[j].count--;
			if (G->adjList[j].count == 0)
			{
				st[++top] = j;
			}
			p = p->next;
		}
	}
}
void AdjacencyList::CriticalPath(GraphAdjList *G)
{
	int ve[max], vl[max],e[max],l[max];
	int i,k;
	edgeNode *p;
	for (i = 0; i < G->numVertexes; i++)
		ve[i] = 0;
	for (i = 0; i < G->numVertexes; i++)//计算各事件最早发生时间//
	{
		p = G->adjList[i].firstedge;
		while (p != NULL)
		{
			k = p->adjvex;
			if (ve[i] + p->weight > ve[k])
				ve[k] = ve[i] + p->weight;
			p = p->next;
		}
	}
	for (i = 0; i < G->numVertexes; i++)
		vl[i] = ve[G->numVertexes - 1];
	for (i = G->numVertexes - 1; i >= 0; i--)//拓扑逆序//
	{
		p = G->adjList[i].firstedge;
		while (p != NULL)
		{
			k = p->adjvex;
			if (vl[k] - p->weight < vl[i])
				vl[i] = vl[k] - p->weight;
			p = p->next;
		}
	}
	for (i = 0; i < G->numVertexes; i++)
	{
		p = G->adjList[i].firstedge;
		while (p != NULL)
		{
			k = p->adjvex;
			e[i] = ve[i];
			l[i] = vl[k] - p->weight;
			if (e[i] == l[i])
				printf("<%d-%d>",i,k);
			p = p->next;
		}
	}
}
int main()
{
	AdjacencyList adjacencyList;
	GraphAdjList *GA = new GraphAdjList;
	adjacencyList.createALGraph(GA);
	adjacencyList.TopSort(GA);
	adjacencyList.CriticalPath(GA);
	adjacencyList.ShowALGraph(GA);
	adjacencyList.DFSTraverse(GA);
	adjacencyList.BFSTraverse(GA);
	adjacencyList.existpath(GA, 1, 3, has);
	adjacencyList.shortpath(GA, 1, 2);
	return 0;
}
//7 8
//0 1 6
//0 2 4
//0 3 5
//1 4 1
//2 4 1
//4 6 9
//3 5 2
//5 6 4
