#include <stdio.h>
#include <stdlib.h>
#define ElementType int

typedef struct SetType * Set;

struct SetType
{
    ElementType Data;
    int Parent;
};

Set Build(int n);
int Find(Set S, ElementType x, int n);
void Union(Set S, ElementType x1, ElementType x2, int n);

int main()
{
    int n;
    ElementType x;
    ElementType x1, x2;
    Set S;

    scanf("%d", &n);
    S = Build(n);
    if(S == NULL)
    {
        return 1;
    }
    scanf("%d", &x);
    printf("%d\n", Find(S, x, n));
    scanf("%d %d", &x1, &x2);
    Union(S, x1, x2, n);
    return 0;
}

Set Build(int n)
{
    Set S;
    int i;

    S = (struct SetType*)malloc(n * sizeof(struct SetType));
    if(S == NULL)
    {
        printf("Build ƒ⁄¥Ê…Í«Î ß∞‹\n");
        return NULL;
    }
    for(i = 0; i < n; i++)
    {
        scanf("%d %d", &S[i].Data, &S[i].Parent);
    }
    return S;
}

int Find(Set S, ElementType x, int n)
{
    int i;
    for(i = 0; (i < n) && (S[i].Data != x); i++)
    {
        ;
    }
    if(i >= n)
    {
        return -1;
    }
    for( ; S[i].Parent >= 0; i = S[i].Parent)
    {
        ;
    }
    return i;
}

void Union(Set S, ElementType x1, ElementType x2, int n)
{
    int Root1, Root2;

    Root1 = Find(S, x1, n);
    Root2 = Find(S, x2, n);
    if(Root1 != Root2)
    {
        if(S[Root1].Parent <= S[Root2].Parent)
        {
            S[Root1].Parent = S[Root1].Parent + S[Root2].Parent;
            S[Root2].Parent = Root1;
        }
        else
        {
            S[Root2].Parent = S[Root1].Parent + S[Root2].Parent;
            S[Root1].Parent = Root2;
        }
    }
}
