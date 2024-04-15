#include <stdio.h>
#include <string.h>
char f[1000], m[1000], left[1000], right[1000];
char DFS(int p, int ml, int mr)
{
    char x = f[p];
    if (ml == mr)
        return x;
    if (ml > mr)
        return 0;
    for (int i = ml; i <= mr; i++)
    {
        if (m[i] == x)
        {
            left[x] = DFS(p + 1, ml, i - 1);
            right[x] = DFS(p + i - ml + 1, i + 1, mr);
            return x;
        }
    }
}
void prt(char x)
{
    if (x == 0)
        return;
    prt(left[x]);
    prt(right[x]);
    printf("%c", x);
}
int main()
{
    gets(f);
    gets(m);
    char rt = DFS(0, 0, strlen(m) - 1);
    prt(rt);
    return 0;
}