#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

typedef int ElementType;
typedef int SetName;

void Initialization(ElementType S[], int n);
void CheckNetwork(ElementType S[], int n);
void Input(ElementType S[]);
void Check(ElementType S[]);
SetName Find(ElementType S[], ElementType m);
void Union(ElementType S[], SetName Root1, SetName Root2);

int main()
{
    ElementType S[MaxSize];
    int n;
    char in;

    scanf("%d", &n);
    Initialization(S, n);
    do
    {
        scanf("%c", &in);
        switch(in)
        {
            case 'I' : Input(S); break;
            case 'C' : Check(S); break;
            case 'S' : CheckNetwork(S, n); break;
        }
    }while(in != 'S');
    return 0;
}

void Initialization(ElementType S[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        S[i] = -1;
    }
}

void Input(ElementType S[])
{
    ElementType x, y;
    SetName Root1, Root2;

    scanf("%d %d", &x, &y);
    Root1 = Find(S, x - 1);
    Root2 = Find(S, y - 1);
    if(Root1 != Root2)
    {
        Union(S, Root1, Root2);
    }
}

SetName Find(ElementType S[], ElementType m)//Â·¾¶Ñ¹Ëõ
{
    if(S[m] < 0)
    {
        return m;
    }
    else
    {
        return S[m] = Find(S, S[m]);
    }
}

void Union(ElementType S[], SetName Root1, SetName Root2)//°´ÖÈ¹é²¢
{
    if(S[Root1] <= S[Root2])
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

void Check(ElementType S[])
{
    ElementType x, y;
    SetName Root1, Root2;

    scanf("%d %d", &x, &y);
    Root1 = Find(S, x - 1);
    Root2 = Find(S, y - 1);
    if(Root1 == Root2)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
}

void CheckNetwork(ElementType S[], int n)
{
    int i, count = 0;

    for(i = 0; i < n; i++)
    {
        if(S[i] < 0)
        {
            count++;
        }
    }
    if(count == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.\n", count);
    }
}
