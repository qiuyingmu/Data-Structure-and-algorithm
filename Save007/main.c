#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    false = 0,
    true  = 1
}bool;

int N, D;
const double radius = 15;
bool issave;
struct Node
{
    int hor;
    int ver;
    bool save;
    bool isjump;
    bool isquery;
};
typedef struct Node * Grap;

struct QNode
{
    struct Node Data;
    struct QNode* Next;
};
struct QueueNode
{
    struct QNode* rear;
    struct QNode* front;
};
typedef struct QueueNode* queue;

void FirstSaving007(Grap G);
void SecondSaving007(Grap G);
void GetSave(Grap G);
void GetJump(Grap G);
bool CalculateSave(int Hor, int Ver);
double CalculateJump(int Hor, int Ver, int x, int y);
void DFS(Grap G, int V);
void BFS(Grap G, int V);
queue BuildQueue();
void Enqueue(queue q, struct Node data);
struct Node Dequeue(queue q);
bool isFull(queue q);

int main()
{
    Grap G;

    scanf("%d %d", &N, &D);
    issave = false;
    G = (Grap)malloc(N * sizeof(struct Node));
    if(G == NULL)
    {
        printf("Grap error.\n");
        exit(1);
    }
    FirstSaving007(G);
    SecondSaving007(G);
    return 0;
}

void FirstSaving007(Grap G)
{
    int i;
    int Hor, Ver;

    for(i = 0; i < N; i++)
    {
        scanf("%d %d", &Hor, &Ver);
        G[i].hor = Hor;
        G[i].ver = Ver;
        G[i].isquery = false;
    }
    GetSave(G);
    GetJump(G);
}

void GetSave(Grap G)
{
    int i;

    for(i = 0; i < N; i++)
    {
        if(CalculateSave(G[i].hor, G[i].ver) == true)
        {
            G[i].save = true;
        }
        else
        {
            G[i].save = false;
        }
    }
}

bool CalculateSave(int Hor, int Ver)
{
    if((abs(Hor - 50) <= D) || (abs(Hor + 50) <= D) ||
        (abs(Ver - 50) <= D) || (abs(Ver + 50) <= D))//只考虑横纵坐标为整形情况
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GetJump(Grap G)
{
    int i;

    for(i = 0; i < N; i++)
    {
        if(CalculateJump(G[i].hor, G[i].ver, 0, 0) <= (D + radius / 2))
        {
            G[i].isjump = true;
        }
        else
        {
            G[i].isjump = false;
        }
    }
}

double CalculateJump(int Hor, int Ver, int x, int y)
{
    return (sqrt((Hor - x) * (Hor - x) + (Ver - y) * (Ver - y)));
}

void SecondSaving007(Grap G)
{
    int i;

    for(i = 0; i < N; i++)
    {
        if(G[i].isjump)
        {
            //DFS(G, i);
            BFS(G, i);
        }
    }
    if(issave == true)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
}

void DFS(Grap G, int V)
{
    int i;

    if(G[V].save)
    {
        issave = true;
        return;
    }
    G[V].isquery = true;
    for(i = 0; i < N; i++)
    {
        if((CalculateJump(G[V].hor, G[V].ver, G[i].hor, G[i].ver) <= D)
           && (G[i].isquery == false))
        {
            DFS(G, i);
        }
    }
}

void BFS(Grap G, int V)
{
    int i;
    queue q;
    struct Node tmp;

    q = BuildQueue();
    G[V].isquery = true;
    Enqueue(q ,G[V]);
    while(!isFull(q))
    {
        tmp = Dequeue(q);
        if(tmp.save == true)
        {
            issave = true;
            return;
        }
        for(i = 0; i < N; i++)
        {
            if((CalculateJump(tmp.hor, tmp.ver, G[i].hor, G[i].ver) <= D)
               && (G[i].isquery == false))
            {
                G[i].isquery = true;
                Enqueue(q, G[i]);
            }
        }
    }
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

void Enqueue(queue q, struct Node data)
{
    struct QNode* Q;

    Q = (struct QNode*)malloc(sizeof(struct QNode));
    if(Q == NULL)
    {
        printf("Enqueue error.\n");
        exit(1);
    }
    Q->Data = data;
    Q->Next = NULL;
    if(q->rear == NULL)
    {
        q->front = Q;
        q->rear = Q;
    }
    else
    {
        q->rear->Next = Q;
        q->rear = Q;
    }
}

struct Node Dequeue(queue q)
{
    struct QNode* FrontCell;
    struct Node FrontNode;

    if(isFull(q))
    {
        printf("queue is full.\n");
        exit(1);
    }
    FrontCell = q->front;
    if(q->front == q->rear)
    {
        q->front = q->rear = NULL;
    }
    else
    {
        q->front = q->front->Next;
    }
    FrontNode = FrontCell->Data;
    free(FrontCell);
    return FrontNode;
}

bool isFull(queue q)
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
