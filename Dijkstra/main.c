#include <stdio.h>
#include <stdlib.h>
#define ElementData int
#define MaxSize 1001
#define Infinity 0x3f3f3f3f

typedef enum
{
    false = 0,
    true  = 1
}bool;

//图
typedef int Vertex;//顶点
struct Node//邻接点
{
    Vertex V;
    ElementData Weight;
    struct Node* Next;
};
typedef struct Node* PtrGraph;
struct EdgeNode//顶点
{
    PtrGraph FirstEdge;
};
typedef struct EdgeNode AdjList;
struct GraphNode//邻接表
{
    int VNums;
    int ENums;
    AdjList Graph[MaxSize];
};
typedef struct GraphNode * LGraph;

ElementData dist[MaxSize];
Vertex path[MaxSize];
Vertex Visit[MaxSize];

LGraph BuildGraph();
void Insert(LGraph G, Vertex V1, Vertex V2, ElementData W);
void Dijkstra(LGraph G, Vertex S);
void InitializerDis(LGraph G, Vertex V);
Vertex FindMin(LGraph G);
void Output(LGraph G);

int main()
{
    LGraph G;
    Vertex S;

    G = BuildGraph();
    scanf("%d", &S);
    Dijkstra(G, S);
    Output(G);
    return 0;
}

LGraph BuildGraph()
{
    LGraph G;

    G = (LGraph)malloc(sizeof(struct GraphNode));
    if(G == NULL)
    {
        printf("LGraph error./n");
        exit(1);
    }
    scanf("%d %d", &G->VNums, &G->ENums);
    for(Vertex V = 1; V <= G->VNums; V++)
    {
        G->Graph[V].FirstEdge = NULL;
    }
    for(int E = 0; E < G->ENums; E++)
    {
        Vertex V1, V2;
        ElementData W;
        scanf("%d %d %d", &V1, &V2, &W);
        Insert(G, V1, V2, W);
    }
    return G;
}

void Insert(LGraph G, Vertex V1, Vertex V2, ElementData W)
{
    PtrGraph P;

    P = (PtrGraph)malloc(sizeof(struct EdgeNode));
    if(P == NULL)
    {
        printf("PtrGraph error.\n");
        exit(1);
    }
    P->V = V2;
    P->Weight = W;
    P->Next = G->Graph[V1].FirstEdge;
    G->Graph[V1].FirstEdge = P;
}

void Dijkstra(LGraph G, Vertex S)
{
    InitializerDis(G, S);
    while(true)
    {
        Vertex V = FindMin(G);
        if(!V)
        {
            break;
        }
        Visit[V] = true;
        for(PtrGraph temp = G->Graph[V].FirstEdge; temp; temp = temp->Next)
        {
            if(Visit[temp->V] == false)
            {
                if(dist[V] + temp->Weight < dist[temp->V])
                {
                    dist[temp->V] = dist[V] + temp->Weight;
                    path[temp->V] = V;
                }
            }
        }
    }
}

void InitializerDis(LGraph G, Vertex V)
{
    PtrGraph P;

    for(int i = 1; i <= G->VNums; i++)
    {
        dist[i] = Infinity;
        path[i] = -1;
        Visit[i] = false;
    }
    dist[V] = 0;
    Visit[V] = true;
    P = G->Graph[V].FirstEdge;
    while(P)
    {
        dist[P->V] = P->Weight;
        path[P->V] = V;
        P = P->Next;
    }
}

Vertex FindMin(LGraph G)
{
    Vertex min = 0;
    ElementData Min = Infinity;

    for(Vertex V = 1; V <= G->VNums; V++)
    {
        if((Visit[V] == false) && (dist[V] < Min))
        {
            min = V;
            Min = dist[V];
        }
    }
    return min;
}

void Output(LGraph G)
{
    for(Vertex V = 1; V <= G->VNums; V++)
    {
        printf("%d ", dist[V]);
    }
    printf("\n");
    for(Vertex V = 1; V <= G->VNums; V++)
    {
        printf("%d ", path[V]);
    }
    printf("\n");
}
