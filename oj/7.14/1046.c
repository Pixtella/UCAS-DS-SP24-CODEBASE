#include <stdio.h>
int n, m, lnk[100][100], has0;
void sort(int* s, int* t)
{
    for (int* i = s; i < t; i++)
    {
        for (int* j = i + 1; j < t; j++)
        {
            if (*i > *j)
            {
                int tmp = *i;
                *i = *j;
                *j = tmp;
            }
        }
    }
}
int read()
{
    int ret = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
    return ret;
}
int main()
{
    n = read();
    m = read();
    for (int i = 0; i < m; i++)
    {
        int u = read(), v = read();
        lnk[u][++lnk[u][0]] = v;
        if (!u || !v) has0 = 1;
    }
    for (int i = 1 - has0; i <= n - has0; i++)
    {
        sort(lnk[i] + 1, lnk[i] + lnk[i][0] + 1);
        printf("%d", i);
        for (int j = lnk[i][0]; j; j--)
        {
            if (j == lnk[i][0]) putchar(' ');
            printf("%d%c", lnk[i][j], j == 1 ? '\n' : ',');
        }
        if (!lnk[i][0]) putchar('\n');
    }
    return 0;
}