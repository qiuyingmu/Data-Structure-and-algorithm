#include <stdio.h>
#include <stdlib.h>

#define ElementType int

typedef struct BinTree * PtrBinTree;

PtrBinTree read();

PtrBinTree Insert(ElementType Element, PtrBinTree rear);

PtrBinTree Find(ElementType Element, PtrBinTree BST);

PtrBinTree Delete(ElementType Element, PtrBinTree BST);

struct BinTree
{
    ElementType Element;
    PtrBinTree Left;
    PtrBinTree Right;
};

int main()
{
    PtrBinTree BST, ADD;
    ElementType Element;

    BST = read();
    scanf("%d", &Element);
    Insert(Element, BST);
    ADD = Find(Element, BST);
    if(ADD)
    {
        printf("%d\n", ADD->Element);
    }
    else
    {
        printf("该数据不存在于二叉树中\n");
    }
    Delete(Element, BST);
    Delete(Element, BST);
    ADD = Find(Element, BST);
    if(ADD)
    {
        printf("%d\n", ADD->Element);
    }
    else
    {
        printf("该数据不存在于二叉树中\n");
    }

    return 0;
}

PtrBinTree read()
{
    ElementType Element;
    PtrBinTree hand, p, rear;
    int N;

    p = (PtrBinTree)malloc(sizeof(struct BinTree));
    if(p == NULL)
    {
        printf("read 函数创建头结点错误\n");
        return NULL;
    }
    rear = p;
    rear->Left = NULL;
    rear->Right = NULL;
    scanf("%d", &N);
    getchar();
    scanf("%d", &Element);
    getchar();
    rear->Element = Element;
    N--;
    while(N--)
    {
        scanf("%d", &Element);
        Insert(Element, rear);
    }
    hand = p;
    p = NULL;
    return hand;
}

PtrBinTree Insert(ElementType Element, PtrBinTree rear)
{
    if(!rear)
    {
        rear = (PtrBinTree)malloc(sizeof(struct BinTree));
        if(rear == NULL)
        {
            printf("Insert 头文件创建失败\n");
            return NULL;
        }
        rear->Element = Element;
        rear->Left = rear->Right = NULL;
    }
    else
    {
        if(Element < rear->Element)
        {
            rear->Left = Insert(Element, rear->Left);
        }
        else if(Element > rear->Element)
        {
            rear->Right = Insert(Element, rear->Right);
        }
    }
    return rear;
}

PtrBinTree Find(ElementType Element, PtrBinTree BST)
{
    while(BST)
    {
        if(Element > BST->Element)
        {
            BST = BST->Right;
        }
        else if(Element < BST->Element)
        {
            BST = BST->Left;
        }
        else
        {
            return BST;
        }
    }
    return NULL;
}

PtrBinTree FinMax(PtrBinTree BST)
{
    while(BST)
    {
        BST = BST->Right;
    }
    return BST;
}

PtrBinTree Delete(ElementType Element, PtrBinTree BST)
{
    PtrBinTree tmp;
    if(!BST)
    {
        printf("要删除的数据没有找到\n");
    }
    else if(Element < BST->Element)
    {
        BST->Left = Delete(Element, BST->Left);
    }
    else if(Element > BST->Element)
    {
        BST->Right = Delete(Element, BST->Right);
    }
    else
    {
        if(BST->Left && BST->Right)
        {
            tmp = FinMax(BST->Left);
            BST->Element = tmp->Element;
            BST->Left = Delete(BST->Element, BST->Left);
        }
        else
        {
            tmp = BST;
            if(BST->Left == NULL)
            {
                BST = BST->Right;
            }
            else if(BST->Right == NULL)
            {
                BST = BST->Left;
            }
            free(tmp);
            tmp = NULL;
        }
    }
    return BST;
}
