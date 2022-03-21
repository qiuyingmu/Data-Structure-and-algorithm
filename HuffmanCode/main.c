#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Maxsize 10//最大的数据个数

typedef struct TreeNode * HuffmanTree;
typedef struct Heap * MinHeap;

int mapping[Maxsize];//本来应该是映射关系，这里简单按顺序处理

struct Heap
{
    HuffmanTree* data;
    int size;
    int maxsize;
};
struct TreeNode
{
    HuffmanTree left, right;
    char item;
    int weight;
};

MinHeap BuildHeap(int n);
HuffmanTree BuildHuffman();
MinHeap InputHeap(int n);
void Establish(MinHeap H);
void PrecDown(MinHeap H, int p);
HuffmanTree Huffman(MinHeap H);
void Insert(MinHeap H, HuffmanTree T);
int IsFull(MinHeap H);
HuffmanTree Delete(MinHeap H);
void Print(HuffmanTree T);
void FreeHuff(HuffmanTree T);
void FreeHeap(MinHeap H);
int WPL(HuffmanTree T, int depth);
void Submit(int n, int codelen);

int main()
{
    int n, m, i, codelen;
    MinHeap H;
    HuffmanTree T;

    scanf("%d", &n);
    getchar();
    H = InputHeap(n);
    T = Huffman(H);
    //Print(T);
    scanf("%d", &m);
    getchar();
    codelen = WPL(T, 0);
    //printf("%d", codelen);
    for(i = 0; i < m; i++)
    {
        Submit(n, codelen);
    }
    FreeHuff(T);
    FreeHeap(H);
    T = H = NULL;
    return 0;
}

MinHeap BuildHeap(int n)
{
    int i;
    MinHeap H;

    H = (MinHeap)malloc(sizeof(struct Heap));
    if(H == NULL)
    {
        printf("BuildHeap error.\n");
        exit(1);
    }
    H->data = (HuffmanTree*)malloc((n + 1) * sizeof(HuffmanTree));
    if(H->data == NULL)
    {
        printf("BuildHeap error.\n");
        exit(1);
    }
    H->maxsize = n;
    H->size = 0;
    H->data[0] = NULL;
    for(i = 1; i <= H->maxsize; i++)
    {
        H->data[i] = BuildHuffman();
    }
    return H;
}

HuffmanTree BuildHuffman()
{
    HuffmanTree T;

    T = (HuffmanTree)malloc(sizeof(struct TreeNode));
    if(T == NULL)
    {
        printf("BuildHuffman error.\n");
        exit(1);
    }
    T->left = T->right = NULL;
    T->weight = 0;
    T->item = '-';
    return T;
}

MinHeap InputHeap(int n)
{
    int i, weight;
    char item;
    MinHeap H;

    H = BuildHeap(n);
    for(i = 1; i <= H->maxsize; i++)
    {
        scanf("%c %d", &item, &weight);
        H->data[i]->item = item;
        H->data[i]->weight = weight;
        mapping[i - 1] = weight;
        getchar();
        H->size++;
    }
    Establish(H);
    return H;
}

void Establish(MinHeap H)
{
    int i;

    for(i = H->size / 2; i > 0; i--)
    {
        PrecDown(H, i);
    }
}

void PrecDown(MinHeap H, int p)
{
    int Parent, Child;
    HuffmanTree Huff;

    Huff = H->data[p];
    for(Parent = p; 2 * Parent <= H->size; Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size)
           && (H->data[Child]->weight > H->data[Child + 1]->weight))
        {
            Child++;
        }
        if(Huff->weight <= H->data[Child]->weight)
        {
            break;
        }
        else
        {
            H->data[Parent] = H->data[Child];
        }
    }
    H->data[Parent] = Huff;
}

HuffmanTree Huffman(MinHeap H)
{
    int i, j = H->size;
    HuffmanTree T;

    for(i = 1; i < j; i++)
    {
        T = (HuffmanTree)malloc(sizeof(struct TreeNode));
        if(T == NULL)
        {
            printf("Huffman error.\n");
            exit(1);
        }
        T->left = Delete(H);
        T->right = Delete(H);
        T->weight = T->left->weight + T->right->weight;
        T->item = '-';
        Insert(H, T);
    }
    T = Delete(H);
    return T;
}

HuffmanTree Delete(MinHeap H)
{
    HuffmanTree MinItem, Huff;
    int Parent, Child;

    MinItem = H->data[1];
    Huff = H->data[H->size--];

    for(Parent = 1; 2 * Parent <= H->size; Parent = Child)
    {
        Child = 2 * Parent;
        if((Child != H->size)
           && (H->data[Child]->weight > H->data[Child + 1]->weight))
        {
            Child++;
        }
        if(H->data[Child]->weight >= Huff->weight)
        {
            break;
        }
        else
        {
            H->data[Parent] = H->data[Child];
        }
    }
    H->data[Parent] = Huff;
    return MinItem;
}

void Insert(MinHeap H, HuffmanTree T)
{
    int i;

    if(IsFull(H))
    {
        printf("This MinHeap is full.\n");
        return;
    }
    for(i = ++H->size; (i > 1) && (H->data[i / 2]->weight > H->data[i]); i /= 2)
    {
        H->data[i] = H->data[i / 2];
    }
    H->data[i] = T;
}

int IsFull(MinHeap H)
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
        printf("%c %d\n", T->item, T->weight);
        Print(T->left);
        Print(T->right);
    }
}

void FreeHuff(HuffmanTree T)
{
    if(T != NULL)
    {
        FreeHuff(T->left);
        FreeHuff(T->right);
    }
    free(T);
}

void FreeHeap(MinHeap H)
{
    free(H->data);
    free(H);
}

int WPL(HuffmanTree T, int depth)//计算最优哈夫曼
{
    if((T->left == NULL) && (T->right == NULL))
    {
        return (depth * T->weight);
    }
    else
    {
        return ((WPL(T->left, depth + 1)) + (WPL(T->right, depth + 1)));
    }
}

void Submit(int n, int codelen)
{
    int i, flag = 1, ADD = 0;
    char item, *code;
    HuffmanTree Huff, pre;

    Huff = BuildHuffman();
    pre = Huff;
    code = (char*)malloc((n - 1) * sizeof(char));
    if(code == NULL)
    {
        printf("SubmitCode error.\n");
        exit(1);
    }
    for(i = 0; i < n; i++)
    {

        scanf("%c %s", &item, code);
        getchar();
        int max = strlen(code);
        ADD += mapping[i] * max;
        int now;
        for(now = 0; (flag == 1) && (now < max); now++)
        {
            if(*(code + now) == '0')
            {
                if(pre->left == NULL)
                {
                    pre->left = BuildHuffman();
                    pre = pre->left;
                }
                else
                {
                    if(pre->left->weight != 0)
                    {
                        flag = 0;
                        break;
                    }
                    else
                    {
                        pre = pre->left;
                    }
                }
            }
            else if(*(code + now) == '1')
            {
                if(pre->right == NULL)
                {
                    pre->right = BuildHuffman();
                    pre = pre->right;
                }
                else
                {
                    if(pre->right->weight != 0)
                    {
                        flag = 0;
                        break;
                    }
                    else
                    {
                        pre = pre->right;
                    }
                }
            }
        }
        if(flag == 1)
        {
            if((pre->left != NULL) && (pre->right != NULL))
            {
                flag = 0;
            }
            else
            {
                pre->item = item;
                pre->weight = mapping[i];
                pre = Huff;
            }
        }
    }
    if(flag == 0)
    {
        printf("No\n");
    }
    else
    {
        if((ADD == codelen))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    FreeHuff(Huff);
    Huff = pre = NULL;
}
