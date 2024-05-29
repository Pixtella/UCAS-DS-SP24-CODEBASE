#include <stdio.h>
char vis[1000000];
int main()
{
    char tt[10000];
    char *buf = tt;
    gets(buf);
    int x;
    while (sscanf(buf, "%d", &x) == 1)
    {
        vis[x] = 1;
        while (*buf != ' ' && *buf != '\0' && *buf != '\n')
            buf++;
        if (*buf == '\0' || *buf == '\n')
            break;
        buf++;
    }
    int fst = 1;
    gets(tt);
    buf = tt;
    while (sscanf(buf, "%d", &x) == 1)
    {
        if (fst)
            fst = 0;
        else
            putchar(' ');
        printf("%d", vis[x]);
        while (*buf != ' ' && *buf != '\0' && *buf != '\n')
            buf++;
        if (*buf == '\0' || *buf == '\n')
            break;
        buf++;
    }
    return 0;
}