#include <stdio.h>
#include <string.h>
#define maxn 100005
int n, s, tot, lnk[maxn], nxt[maxn], son[maxn], w[maxn], dis[maxn], vis[maxn];
void add_e(int x, int y, int z){tot++; son[tot] = y; w[tot] = z; nxt[tot] = lnk[x]; lnk[x] = tot;}
void Dij()
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    for (int i = lnk[s]; i; i = nxt[i])
        dis[son[i]] = w[i];
    vis[s] = 1;
    for (int i = 1; i < n; i++)
    {
        int minn = 0x3f3f3f3f, k = 0;
        for (int j = 1; j <= n; j++)
            if (dis[j] < minn && !vis[j])
                minn = dis[j], k = j;
        vis[k] = 1;
        for (int j = lnk[k]; j; j = nxt[j])
            if (dis[son[j]] > dis[k] + w[j])
                dis[son[j]] = dis[k] + w[j];
    }
}
int main()
{
    scanf("%d%d\n", &n, &s);
    char buf[1000];
    while (gets(buf) && buf[0])
    {
        int x, y, z;
        int ret = sscanf(buf, "%d-%d %d", &x, &y, &z);
        if (ret != 3)
            continue;
        add_e(x, y, z);
    }
    Dij();
    for (int i = 1; i <= n; i++)
        if (i != s)
            printf("%d%c", dis[i], i == n ? '\n' : ',');
    return 0;
}