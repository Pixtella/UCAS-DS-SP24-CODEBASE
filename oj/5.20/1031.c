#include <stdio.h>
int n, m, a[1000][1000];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    int fst = 1;
    for (int xe = n; xe >= 1; xe--)
    {
        for (int ye = m; ye >= 1; ye--)
        {
            if (a[xe][ye] == 0) continue;
            if (!fst) printf("+");
            else fst = 0;
            if (xe == 1 && ye == 1)
            {
                printf("%d", a[xe][ye]);
                continue;
            }
            if (a[xe][ye] != 1)
                printf("%d", a[xe][ye]);
            if (xe >= 2)
                printf("xE%d", xe - 1);
            if (ye >= 2)
                printf("yE%d", ye - 1);
        }
    }
    if (fst) printf("0");
    return 0;
}