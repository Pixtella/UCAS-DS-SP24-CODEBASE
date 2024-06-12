#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, m, a[1000000], b[1000000];
char buf[10000000];
int main()
{
    gets(buf);
    char *token = strtok(buf, " ");
    while (token != NULL)
    {
        a[n++] = atoi(token);
        token = strtok(NULL, " ");
    }
    gets(buf);
    token = strtok(buf, " ");
    while (token != NULL)
    {
        b[m++] = atoi(token);
        token = strtok(NULL, " ");
    }
    int i = 0, j = 0;
    while (i < n || j < m)
    {
        if (i < n && (j == m || a[i] < b[j]))
            printf("%d%c", a[i++], i + j == n + m - 1 ? '\n' : ' ');
        else
            printf("%d%c", b[j++], i + j == n + m - 1 ? '\n' : ' ');
    }
    return 0;
}