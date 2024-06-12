#include <stdio.h>
int hi_b, lo_b, bs, n;
int vis[10000];
int main()
{
    scanf("%d%d%d", &lo_b, &hi_b, &bs);
    n = (hi_b - lo_b) / bs;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vis[i]);
    }
    int lasts = 0, noo = 1;
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0 && (i == 0 || vis[i - 1] == 1))
        {
            lasts = i;
        }
        else if (vis[i] == 1 && i >= 1 && vis[i - 1] == 0)
        {
            printf("0 %d %d\n", lasts * bs + lo_b, (i - lasts) * bs);
            noo = 0;
        }
        else if (vis[i] == 0 && i == n - 1)
        {
            printf("0 %d %d\n", lasts * bs + lo_b, (i - lasts + 1) * bs);
            noo = 0;
        }
    }
    if (noo)
    {
        printf("0 0 0\n");
    }
    return 0;
}