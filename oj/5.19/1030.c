#include <stdio.h>
#include <string.h>
int n, m, a[1000][1000], min_hor[1000], max_ver[1000];
int main()
{
    scanf("%d%d", &n, &m);
    memset(min_hor, 63, sizeof(min_hor));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            if (a[i][j] > max_ver[j])
                max_ver[j] = a[i][j];
            if (a[i][j] < min_hor[i])
                min_hor[i] = a[i][j];
        }
    }
    int fst = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] == min_hor[i] && a[i][j] == max_ver[j])
            {
                if (!fst) putchar(' ');
                else fst = 0;
                printf("%d", a[i][j]);
            }
        }
    }
    return 0;
}