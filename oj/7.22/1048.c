#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 100005
int EOF_flag;
int n, k, s, t, tot, lnk[maxn], nxt[maxn], son[maxn], w[maxn], dis[maxn], vis[maxn], lstx, lsty;
void add_e(int x, int y, int z){tot++; son[tot] = y; w[tot] = z; nxt[tot] = lnk[x]; lnk[x] = tot;}
int read()
{
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        ch = getchar();
        if (ch == EOF) {EOF_flag = 1; return 0;}
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}
void DFS(int x, int cur)
{
    if (x == t)
    {
        printf("yes\n");
        exit(0);
    }
    vis[x] = 1;
    for (int i = lnk[x]; i; i = nxt[i])
        if (!vis[son[i]])
            DFS(son[i], cur + w[i]);
    vis[x] = 0;
}
int main()
{
    scanf("%d", &n);
    while (1)
    {
        int x = read(), y = read(), z = 1;
        if (!EOF_flag)
        {
            if (lstx && lsty)
                add_e(lstx, lsty, 1);
            lstx = x;lsty = y;
        }
        else break;
    }
    s = lstx;
    t = lsty;
    DFS(s, 0);
    printf("no\n");
    return 0;
}