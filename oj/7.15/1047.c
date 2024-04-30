#include <stdio.h>
int n, mat[100][100];
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    char buf[10000];
    while (gets(buf))
    {
        char cmd[100];
        sscanf(buf, "%s", cmd);
        if (cmd[0] == 'I' && cmd[1] == 'V') // InsertVertex
        {
            int x;
            sscanf(buf, "%s%d", cmd, &x);
            n++;
            for (int i = n - 1; i; i--)
            {
                for (int j = n - 1; j; j--)
                {
                    if (i == x || j == x) mat[i][j] = 0;
                    else if (i > x && j > x) mat[i][j] = mat[i - 1][j - 1];
                    else if (i > x) mat[i][j] = mat[i - 1][j];
                    else if (j > x) mat[i][j] = mat[i][j - 1];
                }
            }
        }
        else if (cmd[0] == 'I' && cmd[1] == 'A') // InsertArc
        {
            int x, y;
            sscanf(buf, "%s%d%d", cmd, &x, &y);
            mat[x][y] = mat[y][x] = 1;
        }
        else if (cmd[0] == 'D' && cmd[1] == 'A') // DeleteArc
        {
            int x, y;
            sscanf(buf, "%s%d%d", cmd, &x, &y);
            mat[x][y] = mat[y][x] = 0;
        }
        else if (cmd[0] == 'D' && cmd[1] == 'V') // DeleteVertex
        {
            int x;
            sscanf(buf, "%s%d", cmd, &x);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i >= x && j >= x) mat[i][j] = mat[i + 1][j + 1];
                    else if (i >= x) mat[i][j] = mat[i + 1][j];
                    else if (j >= x) mat[i][j] = mat[i][j + 1];
                }
            }
            n--;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c", mat[i][j], j == n - 1 ? '\n' : ' ');
    return 0;
}