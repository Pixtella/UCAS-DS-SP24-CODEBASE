#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
int n;
char c[100];
int nxt[100][100];
char getsym()
{
    char ch = getchar();
    while (!((ch >= 'a' && ch <= 'z') || (ch == '+') || (ch == '*') || (ch == '/') || (ch == '-')))
        ch = getchar();
    return ch;
}
void DFS(int x)
{
    if (nxt[x][0] && nxt[x][1])
    {
        DFS(nxt[x][1]);
        DFS(nxt[x][0]);
    }
    printf("%c", c[x]);
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        c[i] = getsym();
        char buf[100];
        gets(buf);
        // read integers from buf, we don't know how many integers are there
        int len = strlen(buf);
        int cnt = 0;
        for (int j = 0; j < len; j++)
        {
            if (isdigit(buf[j]))
            {
                int num = 0;
                while (isdigit(buf[j]))
                {
                    num = num * 10 + buf[j] - '0';
                    j++;
                }
                nxt[i][cnt++] = num;
            }
        }
    }
    DFS(0);
    return 0;
}