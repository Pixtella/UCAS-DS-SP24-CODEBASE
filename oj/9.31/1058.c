#include <stdio.h>
int son[1000][2];
int d[1000];
int is_bst(int x)
{
    if (son[x][0] != -1)
    {
        if (d[son[x][0]] > d[x])
            return 0;
        if (!is_bst(son[x][0]))
            return 0;
    }
    if (son[x][1] != -1)
    {
        if (d[son[x][1]] < d[x])
            return 0;
        if (!is_bst(son[x][1]))
            return 0;
    }
    return 1;
}
int main()
{
    int data, lc, rc;
    for (int i = 0;scanf("%d%d%d", &data, &lc, &rc) != EOF; i++)
    {
        d[i] = data;
        son[i][0] = lc;
        son[i][1] = rc;
    }
    printf("%d\n", is_bst(0));
    return 0;
}