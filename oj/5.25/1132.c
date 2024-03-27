#include <stdio.h>
int m1, n1, A[1000][1000], B[1000][1000], ans[1000][1000], V[1000000];
char buf[100000];
int pt;
int EOL_flag;
char GetC()
{
    if (!buf[pt] || buf[pt] == '\n')
    {
        EOL_flag = 1;
        return 0;
    }
    return buf[pt++];
}
int read()
{
    int x = 0, f = 1; char ch = GetC();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = GetC(); if (EOL_flag) return 0; }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = GetC();}
    return x * f;
}
int main()
{
    gets(buf);
    sscanf(buf, "%d%d", &m1, &n1);
    gets(buf);
    while (!EOL_flag)
    {
        V[++V[0]] = read();
    }
    V[0] = 0;
    for (int i = 1; i <= m1; i++)
    {
        gets(buf);
        pt = 0;
        EOL_flag = 0;
        for (int j = 1; j <= n1; j++)
        {
            A[i][j] = read();
            if (A[i][j])
                A[i][j] = V[++V[0]];
        }
    }
    gets(buf);
    pt = 0;
    EOL_flag = 0;
    V[0] = 0;
    while (!EOL_flag)
    {
        V[++V[0]] = read();
    }
    V[0] = 0;
    for (int i = 1; i <= m1; i++)
    {
        gets(buf);
        pt = 0;
        EOL_flag = 0;
        for (int j = 1; j <= n1; j++)
        {
            B[i][j] = read();
            if (B[i][j])
                B[i][j] = V[++V[0]];
        }
    }
    int fstop = 1;
    for (int i = 1; i <= m1; i++)
    {
        for (int j = 1; j <= n1; j++)
        {
            ans[i][j] = A[i][j] + B[i][j];
            if (ans[i][j])
            {
                if (fstop)
                {
                    fstop = 0;
                    printf("%d", ans[i][j]);
                }
                else
                    printf(" %d", ans[i][j]);
            }
        }
    } 
    puts("");
    for (int i = 1; i <= m1; i++)
    {
        for (int j = 1; j <= n1; j++)
        {
            if (ans[i][j] == 0)
                printf("0");
            else
                printf("1");
            putchar(j == n1 ? '\n' : ' ');
        }
    }
    return 0;
}