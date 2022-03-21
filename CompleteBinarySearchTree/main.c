#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* Build(int n);
void read(int* p, int n);
void solve(int pL, int pR, int T, int* p, int* Troot);
int Length(int n);
void Print(int* Troot, int n);

int main()
{
    int n;
    int *p, *Troot;

    scanf("%d", &n);
    p = Build(n);
    Troot = Build(n);
    read(p, n);
    solve(0, n - 1, 0, p, Troot);
    Print(Troot, n);
    free(p);
    free(Troot);
    p = Troot = NULL;
    return 0;
}

int* Build(int n)
{
    int *p = (int*)malloc(n * sizeof(int));
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

void solve(int pL, int pR, int T, int* p, int* Troot)
{
    int n, L, LeftRoot, RightRoot;

    n = pR - pL + 1;
    if(n == 0)
    {
        return;
    }
    L = Length(n);
    *(Troot + T) = *(p + pL + L);
    LeftRoot = 2 * T + 1;
    RightRoot = LeftRoot + 1;
    solve(pL, pL + L - 1,LeftRoot , p, Troot);
    solve(pL + L + 1, pR, RightRoot, p, Troot);
}

int Length(int n)
{
    int i = 1, sum, x, y;

    while(1)
    {
        sum = pow(2, i) - 1;
        if(sum >= n)
        {
            x = pow(2, i - 1) / 2;
            y = sum - n;
            if(y > x)
            {
                sum = (sum / 2) - (y - x);
            }
            else
            {
                sum = sum / 2;
            }
            break;
        }
        else
        {
            i++;
        }
    }
    return sum;
}

void Print(int* Troot, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%d ", *(Troot + i));
    }
}
