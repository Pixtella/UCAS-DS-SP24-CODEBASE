#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, a[1000];
int main()
{
    char buf[100000];
    gets(buf);
    char *token = strtok(buf, " ");
    while (token != NULL)
    {
        a[n++] = atoi(token);
        token = strtok(NULL, " ");
    }
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