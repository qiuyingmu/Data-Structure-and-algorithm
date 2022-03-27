#include <stdio.h>
#include <stdlib.h>
#define MaxSize 1001

typedef enum
{
    false = 0,
    true = 1
}bool;

//访问过的端点
bool Visit[MaxSize];

//邻接表_图
typedef int Vertex;
struct Node//单个端点的信息
{
    Vertex AdjV;//端点下标
    struct Node* Next;//邻接点
};
typedef struct Node* PtrGraph;
struct VNode
{
    PtrGraph FirstEdge;//邻接表第一个
};
typedef struct VNode AdjList;
struct GNode
{
    int EndpointNums;//端点
    int EdgeNums;//边
    AdjList G[MaxSize];//邻接表
};
typedef struct GNode* LGraph;

//队列
struct QNode//队列
{
    Vertex Data;//单个元素的信息
    struct QNode* Next;
};
struct QueueNode
{
    struct QNode* rear;//队列的插头
    struct QNode* front;//队列的删头
};
typedef struct QueueNode* queue;

//函数定义
LGraph BuildGraph();
LGraph EstablishG(int N);
void Insert(LGraph Graph, Vertex V1, Vertex V2);
void SDS(LGraph Graph);
void EmptyVisit(int N);
void Print(LGraph Graph);
void Free(LGraph Graph);
int BFS(LGraph Graph, Vertex V);
queue BuildQueue();
Vertex DeQueue(queue q);
void EnQueue(queue q, Vertex data);
bool IsEmpty(queue q);
void PrintData(int count, int N, Vertex V);

int main()
{
    LGraph Graph;

    Graph = BuildGraph();
    //Print(Graph);
    SDS(Graph);
    Free(Graph);
    return 0;
}

LGraph BuildGraph()
{
    int N, M, i;
    LGraph Graph;

    scanf("%d %d", &N, &M);
    Graph = EstablishG(N);
    Graph->EdgeNums = M;
    for(i = 0; i < M; i++)
    {
        Vertex V1, V2;
        scanf("%d %d", &V1, &V2);
        Insert(Graph, V1, V2);
    }
    return Graph;
}

LGraph EstablishG(int N)
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    if(Graph == NULL)
    {
        printf("BuildGraph error.\n");
        exit(1);
    }
    Graph->EndpointNums = N;
    for(V = 0; V <= Graph->EndpointNums; V++)
    {
        Graph->G[V].FirstEdge = NULL;
    }
    return Graph;
}

void Insert(LGraph Graph, Vertex V1, Vertex V2)
{
    PtrGraph P1, P2;

    P1 = (PtrGraph)malloc(sizeof(struct Node));
    P1->AdjV = V2;
    P1->Next = Graph->G[V1].FirstEdge;
    Graph->G[V1].FirstEdge = P1;
    P2 = (PtrGraph)malloc(sizeof(struct Node));
    P2->AdjV = V1;
    P2->Next = Graph->G[V2].FirstEdge;
    Graph->G[V2].FirstEdge = P2;
}

void SDS(LGraph Graph)
{
    Vertex V;
    int count = 0;

    for(V = 1; V <= Graph->EndpointNums; V++)
    {
        EmptyVisit(Graph->EndpointNums);
        count = BFS(Graph, V);//六度空间问题看做广度优先搜索问题
        PrintData(count, Graph->EndpointNums, V);
    }
}

void EmptyVisit(int N)
{
    Vertex V;

    for(V = 1; V <= N; V++)
    {
        Visit[V] = false;
    }
}

int BFS(LGraph Graph, Vertex V)
{
    queue q;
    PtrGraph tmp;
    Vertex W, last, tail;
    int count = 1, level = 0;

    q = BuildQueue();
    Visit[V] = true;
    EnQueue(q, V);
    last = V;
    while(!IsEmpty(q))
    {
        V = DeQueue(q);
        tmp = Graph->G[V].FirstEdge;
        while(tmp)
        {
            W = tmp->AdjV;
            if(!Visit[W])
            {
                Visit[W] = true;
                EnQueue(q, W);
                count++;
                tail = W;
            }
            tmp = tmp->Next;
        }
        if(V == last)
        {
            level++;
            last = tail;
        }
        if(level == 6)
        {
            break;
        }
    }
    return count;
}

queue BuildQueue()
{
    queue q;

    q = (queue)malloc(sizeof(struct QueueNode));
    if(q == NULL)
    {
        printf("BuildQueue error.\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    return q;
}

void EnQueue(queue q, Vertex data)
{
    struct QNode* Q;

    Q = (struct QNode*)malloc(sizeof(struct QNode));
    if(Q == NULL)
    {
        printf("EnQueue error.\n");
        exit(1);
    }
    Q->Data = data;
    Q->Next = NULL;
    if(q->rear == NULL)
    {
        q->front = q->rear = Q;
    }
    else
    {
        q->rear->Next = Q;
        q->rear = Q;
    }
}

Vertex DeQueue(queue q)
{
    Vertex FrontNode;
    struct QNode* FrontCell;

    if(IsEmpty(q))
    {
        printf("The queue is Empty.\n");
        exit(1);
    }
    FrontCell = q->front;
    if(q->front == q->rear)
    {
        q->front = q->rear;
    }
    else
    {
        q->front = q->front->Next;
    }
    FrontNode = FrontCell->Data;
    free(FrontCell);
    FrontCell = NULL;
    return FrontNode;
}

bool IsEmpty(queue q)
{
    if(q->front == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PrintData(int count, int N, Vertex V)
{
    printf("%d: %.2f%%\n", V, (count * 100.0) / N);
}

void Print(LGraph Graph)
{
    Vertex V;

    for(V = 1; V <= Graph->EndpointNums; V++)
    {
        printf("%d ", V);
        while(Graph->G[V].FirstEdge)
        {
            printf("%d ", Graph->G[V].FirstEdge->AdjV);
            Graph->G[V].FirstEdge = Graph->G[V].FirstEdge->Next;
        }
        printf("\n");
    }
}

void Free(LGraph Graph)
{
    Vertex V;
    PtrGraph tmp;

    for(V = 1; V <= Graph->EndpointNums; V++)
    {
        while(Graph->G[V].FirstEdge)
        {
            tmp = Graph->G[V].FirstEdge->Next;
            Graph->G[V].FirstEdge = Graph->G[V].FirstEdge->Next;
            free(tmp);
            tmp = NULL;
        }
    }
    free(Graph);
}
