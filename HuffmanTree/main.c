#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode * HuffmanTree;
typedef struct HeapTree * Heap;

struct TreeNode
{
    int weight;
    HuffmanTree Left;
    HuffmanTree Right;
};
struct HeapTree
{
    HuffmanTree* Data;
    int size;
    int maxsize;
};

Heap MinHeap(int maxsize);
Heap BuildHeap(int maxsize);
HuffmanTree BuildHuffman();
void Establish(Heap H);
void PercDown(Heap H, int p);
HuffmanTree Huffman(Heap H);
HuffmanTree Delete(Heap H);
void Insert(Heap H, HuffmanTree T);
int IsFull(Heap H);
void Print(HuffmanTree T);

int main()
{
    HuffmanTree T;
    Heap H;
    int maxsize;

    scanf("%d", &maxsize);
    H = MinHeap(maxsize);
    if(H == NULL)
    {
        return 1;
    }
    //printf("%d", H->Data[1]->weight);
    T = Huffman(H);
    if(T == NULL)
    {
        return 1;
    }
    Print(T);
    return 0;
}

Heap MinHeap(int maxsize)
{
    int i;
    int item;
    Heap H;

    H = BuildHeap(maxsize);
    if(H == NULL)
    {
        return NULL;
    }
    for(i = 1; i <= H->maxsize; i++)
    {
        scanf("%d", &item);
        H->Data[i]->weight = item;
        H->size++;
    }
    Establish(H);
    return H;
}

Heap BuildHeap(int maxsize)
{
    int i;
    Heap H;

    H = (Heap)malloc(sizeof(struct HeapTree));
    if(H == NULL)
    {
        printf("BulidHeap_H 内存申请失败\n");
        return NULL;
    }
    H->Data = (HuffmanTree*)malloc((maxsize + 1) * sizeof(HuffmanTree));
    if(H->Data == NULL)
    {
        printf("BuildHeap_Data 内存申请失败\n");
        return NULL;
    }
    H->maxsize = maxsize;
    H->size = 0;
    H->Data[0] = NULL;
    for(i = 1; i <= H->maxsize; i++)
    {
        H->Data[i] = BuildHuffman();
        if(H->Data[i] == NULL)
        {
            return NULL;
        }
    }
    return H;
}

HuffmanTree BuildHuffman()
{
    HuffmanTree H;

    H = (HuffmanTree)malloc(sizeof(struct TreeNode));
    if(H == NULL)
    {
        printf("BuildHuffman 内存申请失败\n");
        return NULL;
    }
    H->Left = H->Right = NULL;
    H->weight = 0;
    return H;
}

void Establish(Heap H)
{
    int i;

    for(i = H->size / 2; i > 0; i--)
    {
        PercDown(H, i);
    }
}

void PercDown(Heap H, int p)
{
    int Parent, Child;
    HuffmanTree Huff;

    Huff = H->Data[p];
    for(Parent = p; 2 * Parent <= H->size; Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size) &&
           (H->Data[Child]->weight > H->Data[Child + 1]->weight))
        {
            Child++;
        }
        if(Huff->weight <= H->Data[Child]->weight)
        {
            break;
        }
        else
        {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = Huff;
}

HuffmanTree Huffman(Heap H)
{
    int i;
    int j = H->size;
    HuffmanTree T;

    for(i = 1; i < j; i++)
    {
        T = (HuffmanTree)malloc(sizeof(struct TreeNode));
        if(T == NULL)
        {
            printf("Huffman 内存申请失败\n");
            return NULL;
        }
        T->Left = Delete(H);
        T->Right = Delete(H);
        T->weight = T->Left->weight + T->Right->weight;
        Insert(H, T);
    }
    T = Delete(H);
    return T;
}

HuffmanTree Delete(Heap H)
{
    HuffmanTree Huff, MinItem;
    int Parent, Child;

    MinItem = H->Data[1];
    Huff = H->Data[H->size--];
    for(Parent = 1; 2 * Parent <= H->size; Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size) &&
           (H->Data[Child]->weight > H->Data[Child + 1]->weight))
        {
            Child++;
        }
        if(Huff->weight <= H->Data[Child]->weight)
        {
            break;
        }
        else
        {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = Huff;
    return MinItem;
}

void Insert(Heap H, HuffmanTree T)
{
    int i;

    if(IsFull(H))
    {
        printf("哈夫曼最小堆已满\n");
        return;
    }
    for(i = ++H->size; (i > 1) && (H->Data[i / 2]->weight > T->weight); i /= 2)
    {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = T;
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

void Print(HuffmanTree T)
{
    if(T)
    {
        printf("%d ", T->weight);
        Print(T->Left);
        Print(T->Right);
    }
}



