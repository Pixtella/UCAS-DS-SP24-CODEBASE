#include <stdio.h>
int n, a[1000];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        if (min != i)
        {
            int t = a[i];
            a[i] = a[min];
            a[min] = t;
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
    return 0;
}