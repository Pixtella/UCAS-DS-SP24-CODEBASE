#include <stdio.h>
#include <string.h>
#define maxn 100005
int EOF_flag;
int n, s, tot, lnk[maxn], nxt[maxn], son[maxn], w[maxn], dis[maxn], vis[maxn], ans[maxn];
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
void DFS(int s, int x, int cur)
{
    if (cur > dis[s]) dis[s] = cur;
    for (int i = lnk[x]; i; i = nxt[i]) DFS(s, son[i], cur + w[i]);
}
int main()
{
    scanf("%d", &n);
    while (1)
    {
        int x = read(), y = read(), z = 1;
        if (!EOF_flag) add_e(x, y, z);
        else break;
    }
    for (int i = 1; i <= n; i++) DFS(i, i, 0);
    for (int i = 1; i <= n; i++) printf("%d%c", dis[i], i == n ? '\n' : ',');
    return 0;
}