#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, a[1000], c[1000];
int main()
{
    char buf[1000];
    gets(buf);
    char *token = strtok(buf, " ");
    while (token != NULL)
    {
        a[n++] = atoi(token);
        token = strtok(NULL, " ");
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[j] < a[i])
                c[i]++;
    for (int i = 0; i < n; i++)
        printf("%d%c", c[i], i == n - 1 ? '\n' : ' ');
    return 0;
}