#include <stdio.h>
char buf[1000], c[100], left[100], right[100];
int fst = 1;
void DFS(int x)
{
    if (fst) fst = 0;
    else printf(" ");
    printf("%c", c[x]);
    if (left[x] != -1) DFS(left[x]);
    if (right[x] != -1) DFS(right[x]);
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
        right[i] = ri;
    }
    DFS(1);
    return 0;
}