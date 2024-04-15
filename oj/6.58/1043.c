#include <stdio.h>
#include <string.h>
int left[1000];
int right[1000];
int LL[1000];
int RR[1000];
int p, n, m, o, rt;
int Readl(int *a)
{
    char buf[1000];
    gets(buf);
    int i = 0;
    char *p = strtok(buf, " ");
    while (p)
    {
        sscanf(p, "%d", &a[i]);
        p = strtok(NULL, " ");
        i++;
    }
    return i;
}
void DFS(int x)
{
    if (x == 0) return;
    if (x == p)
    {
        if (left[x])
            right[LL[0]] = left[x];
        left[x] = LL[0];
        return;
    }
    if (left[x])
        DFS(left[x]);
    if (right[x])
        DFS(right[x]);
}
void prtmid(int x)
{
    if (left[x])
        prtmid(left[x]);
    printf("%d ", x);
    if (right[x])
        prtmid(right[x]);
}
int main()
{
    n = Readl(left);
    Readl(right);
    scanf("%d\n", &p);
    m = Readl(LL);
    Readl(RR);
    o = LL[0] - 1;
    rt = left[0];
    for (int i = 1; i < m; i++)
    {
        left[i + o] = LL[i];
        right[i + o] = RR[i];
    }
    DFS(rt);
    prtmid(rt);
    return 0;
}