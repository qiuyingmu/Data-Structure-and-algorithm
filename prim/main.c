#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define WeightType int
#define MaxVertex 1000
#define INFINITY 0x3F3F3F3F
#define Point 1

typedef enum
{
    false = 0,
    true = 1
}bool;

//图
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef struct ENode* Edge;
struct GNode
{
    int Nv, Ne;
    WeightType Graph[MaxVertex][MaxVertex];
};
typedef struct GNode* MGraph;

MGraph BuildGraph();
void Prim(MGraph G, Vertex S);
void Init(MGraph G);
void InitPrim(MGraph G, Vertex S);
Vertex FindMin(MGraph G, Vertex S);
void OutPut(MGraph G, Vertex S);

//Prim
WeightType Dist[MaxVertex];
Vertex Parent[MaxVertex];
bool MST[MaxVertex];
Vertex test[MaxVertex];

int main()
{
    MGraph G;
    Vertex V;

    G = BuildGraph();
    scanf("%d", &V);
    Prim(G, V);
    OutPut(G, V);
    return 0;
}

MGraph BuildGraph()
{
    MGraph G;
    Edge E;

    G = (MGraph)malloc(sizeof(struct GNode));
    if(G == NULL)
    {
        printf("MGraph error.\n");
        exit(1);
    }
    scanf("%d %d", &G->Nv, &G->Ne);
    for(Vertex V = Point; V <= G->Nv; V++)
    {
        for(Vertex W = Point; W <= G->Nv; W++)
        {
            G->Graph[V][W] = 0;
        }
    }
    if(G->Ne > 0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        if(E == NULL)
        {
            printf("Edge error.\n");
            exit(1);
        }
        for(int i = 0; i < G->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            G->Graph[E->V1][E->V2] = E->Weight;
            G->Graph[E->V2][E->V1] = E->Weight;
        }
        free(E);
        E = NULL;
    }
    return G;
}

void Prim(MGraph G, Vertex S)
{
    int i = Point;
    Vertex V;

    Init(G);
    InitPrim(G, S);
    MST[S] = true;
    test[i] = S;
    i++;
    while(true)
    {
        V = FindMin(G, S);
        if(V == -1)
        {
            break;
        }
        MST[V] = true;
        Dist[V] = 0;
        test[i] = V;
        i++;
        for(Vertex W = Point; W <= G->Nv; W++)
        {
            if(!MST[W] && Dist[W] && G->Graph[V][W])
            {
                if(G->Graph[V][W] < Dist[W])
                {
                    Dist[W] = G->Graph[V][W];
                    Parent[W] = V;
                }
            }
        }
    }
}

void Init(MGraph G)
{
    for(Vertex V = Point; V <= G->Nv; V++)
    {
        Dist[V] = INFINITY;
        Parent[V] = -1;
        MST[V] = false;
    }
}

void InitPrim(MGraph G, Vertex S)
{
    Dist[S] = 0;
    for(Vertex V = Point; V <= G->Nv; V++)
    {
        if(G->Graph[S][V])
        {
            Dist[V] = G->Graph[S][V];
            Parent[V] = S;
        }
    }
}

Vertex FindMin(MGraph G, Vertex S)
{
    WeightType MinDist;
    Vertex Min;

    MinDist = INFINITY;
    Min = -1;
    for(Vertex V = Point; V <= G->Nv; V++)
    {
        if(!MST[V] && Dist[V] && (Dist[V] < MinDist))
        {
            MinDist = Dist[V];
            Min = V;
        }
    }
    return Min;
}

void OutPut(MGraph G, Vertex S)
{
    WeightType Sum;
    Vertex V;

    Sum = 0;
    for(V = Point; V <= G->Nv; V++)
    {
        printf("%d ", V);
    }
    printf("\n");
    for(V = Point; V <= G->Nv; V++)
    {
        printf("%d ", Parent[V]);
        if(Parent[V] != -1)
        {
            Sum += G->Graph[V][Parent[V]];
        }
    }
    printf("\n");
    for(int i = Point; i <= G->Nv; i++)
    {
        printf("%d ", test[i]);
    }
    printf("\n%d\n", Sum);
}

/*7 12
1 2 2
1 4 1
1 3 4
2 4 3
2 5 10
3 4 2
3 6 5
4 6 8
4 7 4
5 4 7
5 7 6
6 7 1
1*/
