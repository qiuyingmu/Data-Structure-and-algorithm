#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* Build(int n);
void read(int* p, int n);
void solve(int preL, int inL, int postL, int n, int* pre, int* in, int* post);

int main()
{
    int n, i;
    int *pre, *in, *post;

    scanf("%d", &n);
    pre = Build(n);
    in = Build(n);
    post = Build(n);
    read(pre, n);
    read(in, n);
    solve(0, 0, 0, n, pre, in, post);
    for(i = 0; i < n; i++)
    {
        printf("%d ", *(post + i));
    }
    free(pre);
    free(in);
    free(post);
    return 0;
}

int* Build(int n)
{
    int* p;

    p = (int*)malloc(n * sizeof(int));
    if(p == NULL)
    {
        printf("Build error.\n");
        exit(1);
    }
    return p;
}

void read(int* p, int n)
{
    int i, x;

    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        *(p + i) = x;
    }
}

void solve(int preL, int inL, int postL, int n, int* pre, int* in, int* post)
{
    int root, L, R, i;

    if(n == 0)
    {
        return;
    }
    if(n == 1)
    {
        *(post + postL) = *(pre + preL);
        return;
    }
    root = *(pre + preL);
    *(post + postL + n - 1) = root;
    for(i = 0; i < n; i++)
    {
        if(*(in + inL + i) == root)
        {
            break;
        }
    }
    L = i;
    R = n - L - 1;
    solve(preL + 1, inL, postL, L, pre, in, post);
    solve(preL + L + 1, inL + L + 1, postL + L, R, pre, in, post);
}
