#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define MaxData 10000 //ÉÚ±ø

typedef struct HeapStruct * MaxHeap;

struct HeapStruct
{
    ElementType* Element;
    int size;
    int maxsize;
};

MaxHeap Build(int MaxSize);

void Establish(MaxHeap H);

int IsFull(MaxHeap H);

int IsEmpty(MaxHeap H);

void PercDown(MaxHeap H, int p);

ElementType Delete(MaxHeap H);

void insert(MaxHeap H, ElementType item);

int main()
{
    MaxHeap H;
    int MaxSize;
    ElementType tmp;

    scanf("%d", &MaxSize);
    H = Build(MaxSize);
    if(H == NULL)
    {
        return 1;
    }
    Establish(H);
    if(IsFull(H))
    {
        printf("¶ÑÒÑÂú\n");
    }
    else
    {
        printf("¶ÑÎ´Âú\n");
    }
    tmp = Delete(H);
    printf("%d\n", tmp);
    insert(H, tmp);
    printf("%d\n", H->Element[1]);
    return 0;
}

MaxHeap Build(int MaxSize)
{
    MaxHeap H;
    H = (MaxHeap)malloc(sizeof(struct HeapStruct));
    if(H == NULL)
    {
        printf("Build_H ÄÚ´æÉêÇëÊ§°Ü\n");
        return NULL;
    }
    H->Element = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
    if(H->Element == NULL)
    {
        printf("Buile_H_Element ÄÚ´æÉêÇëÊ§°Ü\n");
        return NULL;
    }
    H->maxsize = MaxSize;
    H->size = 0;
    H->Element[0] = MaxData;
    return H;
}

void Establish(MaxHeap H)
{
    int i;
    ElementType item;

    for(i = 1; i <= H->maxsize; i++)
    {
        scanf("%d", &item);
        H->Element[i] = item;
        H->size++;
    }
    for(i = H->size / 2; i > 0; i--)
    {
        PercDown(H, i);
    }
}

void PercDown(MaxHeap H, int p)
{
    int Parent, Child;
    ElementType x;

    x = H->Element[p];
    for(Parent = p; (2 * Parent) <= (H->size); Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size) && (H->Element[Child] < H->Element[Child + 1]))
        {
            Child++;
        }
        if(x >= H->Element[Child])
        {
            break;
        }
        else
        {
            H->Element[Parent] = H->Element[Child];
        }
    }
    H->Element[Parent] = x;
}

int IsFull(MaxHeap H)
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

int IsEmpty(MaxHeap H)
{
    if(H->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

ElementType Delete(MaxHeap H)
{
    ElementType tmp, MaxItem;
    int Parent, Child;

    if(IsEmpty(H))
    {
        printf("×î´ó¶ÑÒÑÎª¿Õ\n");
        return;
    }
    MaxItem = H->Element[1];
    tmp = H->Element[H->size--];
    for(Parent = 1; (2 * Parent) <= (H->size); Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size) && (H->Element[Child] < H->Element[Child + 1]))
        {
            Child++;
        }
        if(tmp >= H->Element[Child])
        {
            break;
        }
        else
        {
            H->Element[Parent] = H->Element[Child];
        }
    }
    H->Element[Parent] = tmp;
    return MaxItem;
}

void insert(MaxHeap H, ElementType item)
{
    int i;
    if(IsFull(H))
    {
        printf("×î´ó¶ÑÒÑÂú\n");
        return;
    }
    for(i = ++H->size; H->Element[i / 2] < item; i /= 2)
    {
        H->Element[i] = H->Element[i / 2];
    }
    H->Element[i] = item;
}
