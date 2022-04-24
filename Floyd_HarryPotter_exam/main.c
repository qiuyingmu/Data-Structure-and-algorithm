#include <stdio.h>
#include <stdlib.h>
#define INFINITY 0x3f3f3f3f
#define MaxVertexNums 100
#define Point 1
#define Vertex int
#define WeightType int

struct ENode
{
    Vertex V1;
    Vertex V2;
    WeightType Weight;
};
typedef struct ENode* Edge;
struct GNode
{
    int Nv;
    int Ne;
    WeightType Graph[MaxVertexNums][MaxVertexNums];
};
typedef struct GNode* MGraph;

MGraph BuildGraph();
void FindAnimal(MGraph G);
void Floyd(MGraph G, WeightType D[][MaxVertexNums]);
WeightType FindMaxDise(WeightType D[][MaxVertexNums], Vertex V, int Nv);

int main()
{
    MGraph G;

    G = BuildGraph();
    FindAnimal(G);
    return 0;
}

MGraph BuildGraph()
{
    MGraph G;

    G = (MGraph)malloc(sizeof(struct GNode));
    if(G == NULL)
    {
        printf("MGraph error.\n");
        exit(1);
    }
    scanf("%d %d", &G->Nv, &G->Ne);
    for(Vertex V1 = Point; V1 <= G->Nv; V1++)
    {
        for(Vertex V2 = Point; V2 <= G->Nv; V2++)
        {
            if(V1 == V2)
            {
                G->Graph[V1][V2] = 0;
            }
            else
            {
                G->Graph[V1][V2] = INFINITY;
            }
        }
    }
    if(G->Ne != 0)
    {
        Edge E = (Edge)malloc(sizeof(struct ENode));
        if(E == NULL)
        {
            printf("Edge error.\n");
            exit(1);
        }
        for(int i = Point; i <= G->Ne; i++)
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

void FindAnimal(MGraph G)
{
    WeightType D[MaxVertexNums][MaxVertexNums], MinDist, MaxDist;
    Vertex V, Animal;

    Floyd(G, D);
    MinDist = INFINITY;
    for(V = Point; V <= G->Nv; V++)
    {
        MaxDist = FindMaxDise(D, V, G->Nv);
        if(MaxDist == INFINITY)
        {
            printf("0\n");
            return;
        }
        if(MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = V;
        }
    }
    printf("%d %d\n", Animal, MinDist);
}

void Floyd(MGraph G, WeightType D[][MaxVertexNums])
{
    Vertex V, W, K;

    for(V = Point; V <= G->Nv; V++)
    {
        for(W = Point; W <= G->Nv; W++)
        {
            D[V][W] = G->Graph[V][W];
        }
    }
    for(K = Point; K <= G->Nv; K++)
    {
        for(V = Point; V <= G->Nv; V++)
        {
            for(W = Point; W <= G->Nv; W++)
            {
                if(D[V][W] > D[V][K] + D[K][W])
                {
                    D[V][W] = D[V][K] + D[K][W];
                }
            }
        }
    }
}

WeightType FindMaxDise(WeightType D[][MaxVertexNums], Vertex V, int Nv)
{
    WeightType MaxDist;
    Vertex W;

    MaxDist = 0;
    for(W = Point; W <= Nv; W++)
    {
        if((W != V) && (D[V][W] > MaxDist))
        {
            MaxDist = D[V][W];
        }
    }
    return MaxDist;
}
