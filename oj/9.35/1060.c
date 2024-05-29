#include <stdio.h>
int a[10000], n;
int main()
{
    char tt[10000];
    char *buf = tt;
    gets(buf);
    int x;
    while (sscanf(buf, "%d", &x) == 1)
    {
        a[++n] = x;
        while (*buf != ' ' && *buf != '\0' && *buf != '\n')
            buf++;
        if (*buf == '\0' || *buf == '\n')
            break;
        buf++;
    }
    int lo, hi;
    int fst = 1;
    scanf("%d%d", &lo, &hi);
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > lo && a[i] < hi)
        {
            if (fst)
                fst = 0;
            else
                putchar(' ');
            printf("%d", a[i]);
        }
    }
    return 0;
}