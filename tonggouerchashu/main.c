#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * Tree;

struct TreeNode
{
    int v;
    int flag;
    Tree Left, Right;
};

Tree BuildTree(int N);

Tree NewTree(int V);

Tree Insert(Tree T, int V);

int Judge(Tree T, int N);

int check(Tree T, int V);

void DeleteFlag(Tree T);

void FreeTree(Tree T);

int main()
{
    int N, L, i;
    Tree T;

    scanf("%d", &N);
    while(N)
    {
        scanf("%d", &L);
        T = BuildTree(N);
        if(T == NULL)
        {
            return 1;
        }
        for(i = 0; i < L; i++)
        {
            if(Judge(T, N))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
            DeleteFlag(T);
        }
        FreeTree(T);
        scanf("%d", &N);
    }
    return 0;
}

Tree BuildTree(int N)
{
    int i, V;
    Tree T;

    scanf("%d", &V);
    T = NewTree(V);
    if(T == NULL)
    {
        return NULL;
    }
    for(i = 1; i < N; i++)
    {
        scanf("%d", &V);
        T = Insert(T, V);
        if(T == NULL)
        {
            return NULL;
        }
    }
    return T;
}

Tree NewTree(int V)
{
    Tree T;

    T = (Tree)malloc(sizeof(struct TreeNode));
    if(T == NULL)
    {
        printf("NewTree ƒ⁄¥Ê…Í«Î ß∞‹\n");
        return NULL;
    }
    T->flag = 0;
    T->v = V;
    T->Left = T->Right = NULL;
    return T;
}

Tree Insert(Tree T, int V)
{
    if(T == NULL)
    {
        T = NewTree(V);
        if(T == NULL)
        {
            printf("Insert ƒ⁄¥Ê…Í«Î ß∞‹\n");
        }
    }
    else
    {
        if(V < T->v)
        {
            T->Left = Insert(T->Left, V);
        }
        else if(V > T->v)
        {
            T->Right = Insert(T->Right, V);
        }
    }
    return T;
}

int Judge(Tree T, int N)
{
    int i, V;
    int flag = 0;

    scanf("%d", &V);
    if(V != T->v)
    {
        flag = 1;
    }
    else
    {
        T->flag = 1;
    }
    for(i = 1; i < N; i++)
    {
        scanf("%d", &V);
        if((flag == 0) && (check(T, V) == 0))
        {
            flag = 1;
        }
    }
    if(flag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int check(Tree T, int V)
{
    if(T->flag == 1)
    {
        if(V < T->v)
        {
            return check(T->Left, V);
        }
        else if(V > T->v)
        {
            return check(T->Right, V);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(V == T->v)
        {
            T->flag = 1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void DeleteFlag(Tree T)
{
    if(T->Left)
    {
        DeleteFlag(T->Left);
    }
    if(T->Right)
    {
         DeleteFlag(T->Right);
    }
    T->flag = 0;
}

void FreeTree(Tree T)
{
    if(T->Left)
    {
        DeleteFlag(T->Left);
    }
    if(T->Right)
    {
         DeleteFlag(T->Right);
    }
    free(T);
}
