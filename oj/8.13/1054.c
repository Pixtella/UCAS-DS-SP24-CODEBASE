#include <stdio.h>
int n, blk_st[1000], blk_siz[1000];
int main()
{
    char buf[100];
    while (gets(buf))
    {
        int tag, st, size;
        int t = sscanf(buf, "%d%d%d", &tag, &st, &size);
        if (t == 0) continue;
        if (buf[0] == '\0') continue;
        n++;
        blk_st[n] = st;
        blk_siz[n] = size;
    }
    while (1)
    {
        int merged = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (blk_st[i] + blk_siz[i] == blk_st[j])
                {
                    blk_siz[i] += blk_siz[j];
                    blk_st[j] = blk_st[n];
                    blk_siz[j] = blk_siz[n];
                    n--;
                    merged = 1;
                    goto flag;
                }
            }
        }
        flag:
        if (!merged) break;
        continue;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (blk_st[j] > blk_st[j + 1])
            {
                int t = blk_st[j];
                blk_st[j] = blk_st[j + 1];
                blk_st[j + 1] = t;
                t = blk_siz[j];
                blk_siz[j] = blk_siz[j + 1];
                blk_siz[j + 1] = t;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("0 %d %d\n", blk_st[i], blk_siz[i]);
    }
    return 0;
}