#include <stdio.h>
#define MinData 0
#define MaxVNums 20
#define MaxENums 465

int Nv, Ne;
int G[MaxVNums][MaxVNums];

typedef struct
{
    int V1, V2, Weight;
}Edge;
struct M //MST,MinHeap
{
    Edge E[MaxENums];
    int size;
}MST, MinH;
int parent[MaxVNums];

void BuildGraph();
void Init();
void Kruskal();
void InsertMinH(Edge E);
int Find(int V);
void Union(int x, int y);
void Output();

int main()
{
    scanf("%d %d", &Nv, &Ne);
    Init();
    BuildGraph();
    Kruskal();
    Output();
    return 0;
}

void BuildGraph()
{
    Edge E;

    for(int i = 0; i < Nv; i++)
    {
        for(int j = 0; j < Ne; j++)
        {
            G[i][j] = 0;
        }
    }
    if(Ne > 0)
    {
        for(int i = 0; i < Ne; i++)
        {
            scanf("%d %d %d", &E.V1, &E.V2, &E.Weight);
            G[E.V1 - 1][E.V2 - 1] = E.Weight;
            G[E.V2 - 1][E.V1 - 1] = E.Weight;
            InsertMinH(E);
        }
    }
}

void Init()
{
    Edge Temp;

    Temp.V1 = Temp.V2 = -1;
    Temp.Weight = MinData;
    MST.size = 0;
    MinH.size = 0;
    for(int i = 0; i < Ne; i++)
    {
        MST.E[i] = Temp;
        if(i == 0)
        {
            MinH.E[i] = Temp;
        }
    }
    for(int i = 0; i < Nv; i++)
    {
        parent[i] = -1;
    }
}

void InsertMinH(Edge E)
{
    int i;

    if(MinH.size == Ne)
    {
        return;
    }
    for(i = ++MinH.size; MinH.E[i / 2].Weight > E.Weight; i /= 2)
    {
        MinH.E[i] = MinH.E[i / 2];
    }
    MinH.E[i] = E;
}

Edge DeleteMinH()
{
    Edge item, tmp;
    int Father, Child;

    item = MinH.E[1];
    tmp = MinH.E[MinH.size--];
    for(Father =1; Father * 2 <= MinH.size; Father = Child)
    {
        Child = 2 * Father;
        if((Child != MinH.size) &&
           (MinH.E[Child].Weight > MinH.E[Child + 1].Weight))
        {
            Child++;
        }
        if(MinH.E[Child].Weight >= tmp.Weight)
        {
            break;
        }
        else
        {
            MinH.E[Father] = MinH.E[Child];
        }
    }
    MinH.E[Father] = tmp;
    return item;
}

void Kruskal()
{
    Edge E;

    while((MST.size != Nv - 1) && (MinH.size != 0))
    {
        E = DeleteMinH();
        if(Find(E.V1) != Find(E.V2))
        {
            Union(E.V1, E.V2);
            MST.E[MST.size++] = E;
        }
    }
}

int Find(int V)
{
    if(parent[V] < 0)
    {
        return V;
    }
    else
    {
        return parent[V] = Find(parent[V]);
    }
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);
    if(x != y)
    {
        if(parent[x] <= parent[y])
        {
            parent[x] = parent[x] + parent[y];
            parent[y] = x;
        }
        else
        {
            parent[y] = parent[x] + parent[y];
            parent[x] = y;
        }
    }
}

void Output()
{
    for(int i = 0; i < MST.size; i++)
    {
        printf("%d %d %d\n", MST.E[i].V1, MST.E[i].V2, MST.E[i].Weight);
    }
}
