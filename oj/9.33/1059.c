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
    int lo;
    int fst = 1;
    scanf("%d", &lo);
    for (int i = n; i >= 1; i--)
    {
        if (a[i] >= lo)
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