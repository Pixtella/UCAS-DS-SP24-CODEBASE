#include <stdio.h>
char buf[100];
char ch[1000];
int left[1000], right[1000], dep[1000], fa[1000];
int p;
int cnt = 1;
void DFS(int x)
{
    ch[x] = buf[p++];
    if (!buf[p]) return;
    if (buf[p] == '^')
    {
        p++;
    }
    else
    {
        cnt++;
        left[x] = cnt;
        dep[left[x]] = dep[x] + 1;
        fa[left[x]] = x;
        DFS(left[x]);
    }
    if (!buf[p]) return;
    if (buf[p] == '^')
    {
        p++;
        return;
    }
    cnt++;
    right[x] = cnt;
    dep[right[x]] = dep[x] + 1;
    fa[right[x]] = x;
    DFS(right[x]);
}
int main()
{
    gets(buf);
    DFS(1);
    char c1, c2;
    scanf("%c %c", &c1, &c2);
    int u, v;
    for (int i = 1; i < 1000; i++)
    {
        if (ch[i] == c1) u = i;
        if (ch[i] == c2) v = i;
    }
    u = fa[u];
    v = fa[v];
    while (u != v)
    {
        if (dep[u] > dep[v]) u = fa[u];
        else if (dep[u] < dep[v]) v = fa[v];
        else
        {
            u = fa[u];
            v = fa[v];
        }
    }
    printf("%c", ch[u]);
    return 0;
}