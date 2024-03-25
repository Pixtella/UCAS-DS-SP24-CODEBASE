#include <stdio.h>
int a[100000], n, x;
int flg;
int read()
{
    int ret = 0, f = 1; char ch =getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '\n')
        {
            flg = 1;
            return -155;
        }
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + ch - '0';
        ch = getchar();
    }
    if (ch == '\n')
    {
        flg = 1;
    }
    return ret * f;
}
int main()
{
    while (flg == 0)
    {
        a[++n] = read();
    }
    if (a[n] == -155)
    {
        n--;
    }
    x = read();
    if (n == 1)
    {
        printf("NULL\n");
    }
    else
    {
        for (int i = x + 1; i < n; i++)
            a[i] = a[i + 1];
        n -= 1;
        for (int i = 1; i <= n; i++)
        {
            printf("%d%c", a[i], i == n ? '\n' : ' ');
        }
    }


    return 0;
}