#include <stdio.h>
#include <string.h>
char buf[1000];
int L[1000];
int R[1000];
int fa[1000];
int main()
{
    gets(buf);
    int i = 0;
    char *p = strtok(buf, " ");
    while (p)
    {
        sscanf(p, "%d", &L[i]);
        p = strtok(NULL, " ");
        if (i && L[i])
        fa[L[i]] = i;
        i++;
    }
    gets(buf);
    i = 0;
    p = strtok(buf, " ");
    while (p)
    {
        sscanf(p, "%d", &R[i]);
        p = strtok(NULL, " ");
        if (i && R[i])
        fa[R[i]] = i;
        i++;
    }
    int u, v;
    scanf("%d %d", &u, &v);
    if (u == v)
    {
        printf("0\n");
        return 0;
    }
    while (u)
    {
        if (u == v)
        {
            printf("1\n");
            return 0;
        }
        u = fa[u];
    }
    printf("0\n");
    return 0;
}