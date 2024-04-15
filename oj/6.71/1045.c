#include <stdio.h>
char buf[1000], c[100], left[100], right[100], nei[100];
int fst = 1;
void DFS(int x, int dep)
{
    for (int i = 0; i < dep; i++)
        printf("-");
    printf("%c\n", c[x]);
    for (int t = left[x]; t; t = nei[t])
    {
        if (t == -1) break;
        DFS(t, dep + 1);
    }
}
int main()
{
    int i = 0;
    while (gets(buf))
    {
        i++;
        char ci;
        int li, ri;
        int ret = sscanf(buf, "%c %d %d", &ci, &li, &ri);
        if (ret != 3) break;
        c[i] = ci;
        left[i] = li;
        nei[i] = ri;
    }
    DFS(1, 0);
    return 0;
}