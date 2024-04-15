#include <stdio.h>
#include <string.h>
char buf[1000];
int fa[1000];
int main()
{
    gets(buf);
    int i = 0;
    char *p = strtok(buf, " ");
    while (p)
    {
        sscanf(p, "%d", &fa[i]);
        p = strtok(NULL, " ");
        i++;
    }
    gets(buf);
    gets(buf);
    int u, v;
    scanf("%d %d", &u, &v);
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