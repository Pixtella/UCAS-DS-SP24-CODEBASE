#include <stdio.h>
#include <stdlib.h>
int n, s[1000], fst[1000], lst[1000];
int tot, lnk[1000], nxt[1000], son[1000];
int vis[1000];
void add_e(int x, int y){tot++; son[tot] = y; nxt[tot] = lnk[x]; lnk[x] = tot;}
void DFS(int x)
{
    if (vis[x])
    {
        printf("yes\n");
        exit(0);
    }
    vis[x] = 1;
    for (int i = lnk[x]; i; i = nxt[i])
        DFS(son[i]);
    vis[x] = 0;
}
int main()
{
    scanf("%d\n", &n);
    char buf[10000];
    gets(buf);
    // read integers from buf and store them in s, we don't know the number of integers
    int j = 0;
    while (buf[j] != '\0')
    {
        while (buf[j] == ' ')
            j++;
        if (buf[j] == '\0' || buf[j] == '\n')
            break;
        s[tot++] = 0;
        while (buf[j] >= '0' && buf[j] <= '9')
            s[tot - 1] = s[tot - 1] * 10 + buf[j++] - '0';
    }
    tot = 0;
    for (int i = 0; i <= n; i++)
        scanf("%d", &fst[i]);
    for (int i = 0; i <= n; i++)
        scanf("%d", &lst[i]);
    for (int i = 1; i <= n; i++)
        for (int j = fst[i]; j < lst[i]; j++)
            add_e(i, s[j]);
    for (int i = 1; i <= n; i++)
        DFS(i);
    printf("no\n");
    return 0;
}