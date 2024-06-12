#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int emb[100][100];
int main()
{
    char buf[100];
    while (fgets(buf, 100, stdin) != NULL)
    {
        int a[100] = {0};
        int n = 0;
        char *token = strtok(buf, " ");
        while (token != NULL)
        {
            a[n++] = atoi(token);
            token = strtok(NULL, " ");
        }
        int size = a[0];
        for (int i = 1; i < n; i++)
            emb[size][++emb[size][0]] = a[i];
    }
    for (int b = 0; b < 20; b++)
    {
        for (int i = 1; i <= emb[b][0]; i++)
        {
            for (int j = 1; j <= emb[b][0]; j++)
            {
                if (emb[b][i] + (1 << b) == emb[b][j] && (emb[b][i] % (1 << (b + 1))) == 0)
                {
                    int tep[100] = {0};
                    for (int k = 1; k <= emb[b][0]; k++)
                        if (k != i && k != j)
                            tep[++tep[0]] = emb[b][k];
                    emb[b + 1][++emb[b + 1][0]] = emb[b][i];
                    for (int i = 0; i < 100; i++)
                        emb[b][i] = tep[i];
                    b--;
                    goto flag;
                }
            }
        }
        flag:
        continue;
    }
    for (int i = 0; i < 20; i++)
    {
        if (emb[i][0] != 0)
        {
            printf("%d", i);
            for (int t1 = 1; t1 <= emb[i][0]; t1++)
            {
                for (int t2 = 1; t2 < emb[i][0]; t2++)
                {
                    if (emb[i][t2] > emb[i][t2 + 1])
                    {
                        int temp = emb[i][t2];
                        emb[i][t2] = emb[i][t2 + 1];
                        emb[i][t2 + 1] = temp;
                    }
                }
            }
            for (int j = 1; j <= emb[i][0]; j++)
                printf(" %d", emb[i][j]);
            printf("\n");
        }
    }
    return 0;
}