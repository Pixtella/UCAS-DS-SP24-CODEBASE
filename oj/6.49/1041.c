#include <stdio.h>
char buf[1000], c[100], left[100], right[100], nei[100];
int fail, dep[100], cnt[100];
void DFS(int x)
{
    cnt[dep[x]]++;
    if (left[x] != -1)
    {
        if (left[x] != x * 2) fail = 1;
        dep[left[x]] = dep[x] + 1;
        DFS(left[x]);
    }
    if (right[x] != -1)
    {
        if (right[x] != x * 2 + 1) fail = 1;
        dep[right[x]] = dep[x] + 1;
        DFS(right[x]);
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
    DFS(1);
    for (int i = 0; i < 20; i++)
    {
        if (cnt[i] != (1 << i))
        {
            if (cnt[i + 1] != 0)
                fail = 1;
            break;
        }
    }
    if (fail)
        printf("No\n");
    else
        printf("Yes\n");
    return 0;
}