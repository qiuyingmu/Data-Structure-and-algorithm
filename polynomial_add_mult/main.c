#include <stdio.h>
#include <stdlib.h>

typedef struct polynode * ptr_polynode;

struct polynode{
    int coef;
    int expon;
    ptr_polynode link;
};

ptr_polynode read();

void attach(int c, int e, ptr_polynode* rear);

ptr_polynode add_poly(ptr_polynode p1, ptr_polynode p2);

ptr_polynode mult_poly(ptr_polynode p1, ptr_polynode p2);

void print_poly(ptr_polynode p);

void free_poly(ptr_polynode p);

int main()
{
    ptr_polynode p1, p2, p_add, p_mult;

    p1 = read();
    p2 = read();
    p_add = add_poly(p1, p2);
    p_mult = mult_poly(p1, p2);
    print_poly(p_add);
    print_poly(p_mult);
    free_poly(p1);
    p1 = NULL;
    free_poly(p2);
    p2 = NULL;
    free_poly(p_add);
    p_add = NULL;
    free_poly(p_mult);
    p_mult = NULL;

    return 0;
}

ptr_polynode read()
{
    int n, c, e;
    ptr_polynode p, rear, t;

    p = (ptr_polynode)malloc(sizeof(struct polynode));
    if(p == NULL)
    {
        printf("read 内存开辟失败\n");
        return NULL;
    }
    p->link = NULL;
    rear = p;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d %d", &c, &e);
        attach(c, e, &rear);
    }
    t = p;
    p = p->link;
    free(t);
    t = NULL;
    rear = NULL;
    return p;
}

void attach(int c, int e, ptr_polynode* rear)
{
    ptr_polynode p;

    p = (ptr_polynode)malloc(sizeof(struct polynode));
    if(p == NULL)
    {
        printf("attach 内存开辟失败\n");
        return;
    }
    p->link = NULL;
    p->coef = c;
    p->expon = e;
    (*rear)->link = p;
    *rear = p;
    p = NULL;
}

ptr_polynode add_poly(ptr_polynode p1, ptr_polynode p2)
{
    int sum = 0;
    ptr_polynode t1, t2, rear, p, temp;

    t1 = p1;
    t2 = p2;
    p = (ptr_polynode)malloc(sizeof(struct polynode));
    if(p == NULL)
    {
        printf("add_poly 头结点创建失败\n");
        return NULL;
    }
    p->link = NULL;
    rear = p;
    while(t1 && t2)
    {
        if(t1->expon == t2->expon)
        {
            sum = t1->coef + t2->coef;
            attach(sum, t1->expon, &rear);
            t1 = t1->link;
            t2 = t2->link;
        }
        else if(t1->expon > t2->expon)
        {
            attach(t1->coef, t1->expon, &rear);
            t1 = t1->link;
        }
        else
        {
            attach(t2->coef, t2->expon, &rear);
            t2 = t2->link;
        }
    }
    while(t1)
    {
        attach(t1->coef, t1->expon, &rear);
        t1 = t1->link;
    }
    while(t2)
    {
        attach(t2->coef, t2->expon, &rear);
        t2 = t2->link;
    }
    rear->link = NULL;
    temp = p;
    p = p->link;
    free(temp);
    temp = NULL;
    rear = NULL;
    return p;
}

void print_poly(ptr_polynode p)
{
    int flag = 1;

    while(p)
    {
        if(flag)
        {
            flag = 0;
        }
        else
        {
            printf(" ");
        }
        printf("%d %d", p->coef, p->expon);
        p = p->link;
    }
    printf("\n");
}

ptr_polynode mult_poly(ptr_polynode p1, ptr_polynode p2)
{
    int c, e;
    ptr_polynode t1, t2, p, rear, temp;

    if(!p1 || !p2)
    {
        printf("p1, p2多项式为空\n");
        return NULL;
    }
    t1 = p1;
    t2 = p2;
    p = (ptr_polynode)malloc(sizeof(struct polynode));
    if(p == NULL)
    {
        printf("mult_poly 头结点创建失败\n");
        return NULL;
    }
    p->link = NULL;
    rear = p;
    while(t2)
    {
        attach(t1->coef * t2->coef, t1->expon + t2->expon, &rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1)
    {
        t2 = p2;
        rear = p;
        while(t2)
        {
            c = t1->coef * t2->coef;
            e = t1->expon + t2->expon;
            while(rear->link && rear->link->expon > e)
            {
                rear = rear->link;
            }
            if(rear->link && rear->link->expon == e)
            {
                if(rear->link->coef + c)
                {
                    rear->link->coef += c;
                }
                else
                {
                    temp = rear->link;
                    rear->link = temp->link;
                    free(temp);
                    temp = NULL;
                }
            }
            else
            {
                temp = (ptr_polynode)malloc(sizeof(struct polynode));
                if(temp == NULL)
                {
                    printf("mult_poly 头结点创建失败\n");
                    return NULL;
                }
                temp->coef = c;
                temp->expon = e;
                temp->link = rear->link;
                rear->link = temp;
                rear = rear->link;
                temp = NULL;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    temp = p;
    p = p->link;
    free(temp);
    temp = NULL;
    rear = NULL;
    return p;
}

void free_poly(ptr_polynode p)
{
    ptr_polynode temp;

    while(p)
    {
        temp = p;
        p = p->link;
        free(temp);
    }
    temp = NULL;
}
