#include<iostream>
#define max 100
#define INF 0x3f3f3f3f
using namespace std;
int visited[100];//��־����//
bool has;
typedef struct EdgeNode {
	int adjvex;//����i���ڵĶ�����//
	struct EdgeNode *next;//��һ���߽��ָ����//
	int weight;
}edgeNode;//�߽������//
typedef struct VertexNode
{
	char data;//������Ϣ//
	int count;//��Ŷ������//
	edgeNode *firstedge;//ָ���һ���߽��//
}VertexNode,AdjList[100];//�ٽ��ͷ�������,AdjList���ڽӱ����ͣ�100-���������//
typedef struct {
	AdjList adjList;//�ڽӱ�//
	int numVertexes, numEdges;//������������//
}GraphAdjList;
typedef struct
{
	int data;
	int parent;

}QUERE;
//�ڽӾ���ṹ��//
typedef struct
{
	int no;//������//
	//������Ϣ//
}VertexType;
typedef struct
{
	int edges[max][max];
	int n, e;//������������//
	VertexType vexs[max];
}MGraph;
class AdjacencyList {
public:
	void CreateALGraph(GraphAdjList *G);//����ͼ�ڽӱ�Ĵ���//
	void createALGraph(GraphAdjList *G);//����ͼ�ڽӱ�Ĵ���//
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
//����ͼ�ڽӱ���//
void AdjacencyList::CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	edgeNode *e;
	cin >> G->numVertexes >> G->numEdges;//���붥�����ͱ���//
	//���붥����Ϣ�����������//
	for (i = 0; i < G->numVertexes; i++)
	{
		cin >> G->adjList[i].data;//���붥����Ϣ//
		G->adjList[i].firstedge = NULL;//�߱���Ϊ�ձ�//
	}
	for (k = 0; k < G->numEdges; k++)
	{
		cin >> i >> j;//������ϵĶ������//
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
//����ͼ�ڽӱ���//
void AdjacencyList::createALGraph(GraphAdjList *G)
{
	int i, j, k, weight;
	int x, y;//��ͷ����β����//
	edgeNode *e;
	scanf("%d%d", &G->numVertexes, &G->numEdges);//���붥�����ͱ���//
	//���붥����Ϣ�����������//
	for (i =0 ;i <G->numVertexes; i++)
	{
		G->adjList[i].data = i;
		G->adjList[i].firstedge = NULL;//�߱���Ϊ�ձ�//
	}
	for (k = 0; k < G->numEdges; k++)
	{
		scanf("%d%d%d", &i, &j,&weight);//������ϵĶ������//
		x = locate(G, i);
		y = locate(G, j);
		e = (edgeNode*)malloc(sizeof(edgeNode));
		e->weight = weight;
		e->adjvex = y;
		e->next = G->adjList[x].firstedge;
		G->adjList[x].firstedge = e;
	}
}
int AdjacencyList::locate(GraphAdjList *G, int v)//���Ҷ�����˳�����λ��//
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
		cout << "����" << i << ":" << G->adjList[i].data << "--firstedge--";
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
	EdgeNode *p;//��iΪ��ʼ�����ڽӱ����dfs����//
	visited[i] = 1;//���ʲ������//
	cout << G->adjList[i].data << "--";
	p = G->adjList[i].firstedge;//pָ�򶥵�i�ĵ�һ���ڽӵ�//
	while (p)
	{
		if (!visited[p->adjvex])
		{
			DFS(G, p->adjvex);//�ݹ鷵��//
		}
		p = p->next;//����һ���ڽӵ�//
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
		visited[i] = 0;//��־�����ʼ��//
	}
	printf("%2d", v);//������ʽ����//
	visited[v] = 1;
	rear = (rear + 1) % 100;
	queue[rear] = v;//v����//
	while (front != rear)//���в�Ϊ�գ�ѭ��//
	{
		front = (front + 1) % 100;
		w = queue[front];//���Ӹ���w//
		p = G->adjList[w].firstedge;
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0)//��ǰ�ڽӽڵ�δ����//
			{
				printf("%2d", p->adjvex);//�����ڽӽڵ�//
				visited[p->adjvex] = 1;
				rear = (rear + 1) % 100;
				queue[rear] = p->adjvex;//�ö������//
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
void AdjacencyList::existpath(GraphAdjList *G, int u, int v, bool &has)//has�ж�u-v�Ƿ���·��//
{
	int w;
	edgeNode *p;
	visited[u] = 1;
	if (u == v)
	{
		has = true;
		return;
	}
	p = G->adjList[u].firstedge;//ָ��u�ĵ�һ�����ڽ��//
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
	rear++;//����u����//
	qu[rear].data = u;
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear)
	{
		front++;
		w = qu[front].data;//����//
		if (w == v)//�ҵ�vʱ���·��֮�沢�˳�//
		{
			i = front;
			while (qu[i].parent != -1)
			{
				printf("%2d", qu[i].data);
				i = qu[i].parent;//��ǰ��//
			}
			printf("%2d\n", qu[i].data);
			break;
		}
		p = G->adjList[w].firstedge;//��w�ĵ�һ���ڽӵ�//
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
	int dist[max];//�����Դ��v������i��Ŀǰ���·�����ȣ���ֵΪȨֵ�����ܱ����´�С//
	int path[max];//���浱ǰ���·����ǰһ������ı��//
	int s[max];//0-δ�ҵ�Դ�㵽i�����·��;1-�ҵ�//
	int mindis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];
		s[i] = 0;
		if (g.edges[v][i] < INF)//???//
			path[i] = v;//��v��i�бߣ���i��ǰһ������Ϊv???//
		else
			path[i] = -1;
	}
	s[v] = 1;//���v�������//
	path[v] = 0;
	for (i = 0; i < g.n; i++)//ѭ��ֱ�����ж�������·�������//
	{
		mindis = INF;
		for(j=0;j<g.n;j++)
			if (s[j] == 0 && dist[j] < mindis)//ѡȡ����s���Ҿ�����С����Ķ���u//
			{
				u = j;
				mindis = dist[j];
			}
		s[u] = 1;
		for(j=0;j<g.n;j++)
			if (g.edges[u][j] < INF&&dist[u] + g.edges[u][j] < dist[j])//�޸Ĳ���s�ж���ľ���//
			{
				dist[j] = dist[u] + g.edges[u][j];
				path[j] = u;
			}
	}
	Dispath(g, dist, path, s, v);//������·��//
}
void AdjacencyList::Dispath(MGraph g, int dist[], int path[], int S[], int v)
{
	int i, j, k;
	int apath[max], d;//���һ�����·�������򣩼��䶥�����//
	for(i=0;i<g.n;i++)//ѭ�����v��i��·��//
		if (S[i] == 1 && i != v)
		{
			printf("%d-%d:%d", v, i, dist[i]);
			d = 0; apath[d] = i;
			k = path[i];
			if (k == -1)
				printf("��·��\n");
			else
			{
				while (k != v)
				{
					d++;
					apath[d] = k;
					k = path[k];
				}
				d++;
				apath[d]=i;//���·���ϵ����???//
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
				path[i][j] = i;//i��j�б�ʱ//
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
			if (A[i][j] != INF && i != j)//������·��//
			{
				printf("%d-%d", i, j);
				k = path[i][j];
				d = 0; apath[d] = j;//·��������յ�//
				while (k != -1 && k != i)//����м��//
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
				printf("·������Ϊ��%d", A[i][j]);
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
	for (i = 0; i < G->numVertexes; i++)//�����ж�������//
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
			st[++top] = i;//���Ϊ0�����ջ//
		}
	while (top > -1)//ջ�ǿ�ѭ��//
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
	for (i = 0; i < G->numVertexes; i++)//������¼����緢��ʱ��//
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
	for (i = G->numVertexes - 1; i >= 0; i--)//��������//
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
