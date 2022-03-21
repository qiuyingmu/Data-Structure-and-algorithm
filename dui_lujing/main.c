#include <stdio.h>
#include <stdlib.h>

typedef struct HeapTree * Heap;

struct HeapTree
{
    int* Data;
    int size;
    int maxsize;
};

Heap BuildHeap(int n);
void Insert(Heap H, int x);
int IsFull(Heap H);

int main()
{
    int n, m, i, j, x;
    Heap H;

    scanf("%d %d", &n, &m);
    H = BuildHeap(n);
    if(H == NULL)
    {
        return 1;
    }
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        Insert(H, x);
    }
    for(i = 0; i < m; i++)
    {
        scanf("%d", &j);
        printf("%d", H->Data[j]);
        while(j > 1)
        {
            j /= 2;
            printf(" %d", H->Data[j]);
        }
        printf("\n");
    }
    return 0;
}

Heap BuildHeap(int n)
{
    Heap H;
    H = (Heap)malloc(sizeof(struct HeapTree));
    if(H == NULL)
    {
        printf("BuildHeap_Heap ÄÚ´æÉêÇëÊ§°Ü\n");
        return NULL;
    }
    H->Data = (int *)malloc((n + 1) * sizeof(int));
    if(H->Data == NULL)
    {
        printf("BuildHeap_H_Data ÄÚ´æÉêÇëÊ§°Ü\n");
        return NULL;
    }
    H->size = 0;
    H->maxsize = n;
    H->Data[0] = 0;//Å×Æú0´¦µÄÐèÇó
    return H;
}

void Insert(Heap H, int x)
{
    int i;
    if(IsFull(H))
    {
        printf("×îÐ¡¶ÑÒÑÂú\n");
        return;
    }
    for(i = ++H->size; (i > 1) && (H->Data[i / 2] > x); i /= 2)
    {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i]= x;
}

int IsFull(Heap H)
{
    if(H->size == H->maxsize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
