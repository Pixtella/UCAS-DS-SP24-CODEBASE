#include <stdio.h>
#include <string.h>
int n;
char strs[1000][100];
char del[1000];
int main()
{
    char buf[1000];
    while (gets(buf))
    {
        int x;
        sscanf(buf, "%d", &x);
        if (x == 1)
        {
            n++;
            sscanf(buf, "%d %s", &x, strs[n]);
        }
        else if (x == 2)
        {
            char buffer[1000];
            sscanf(buf, "%d %s", &x, buffer);
            for (int i = 1; i <= n; i++)
            {
                if (strcmp(strs[i], buffer) == 0)
                {
                    del[i] = 1;
                }
            }
        }
        else if (x == 3)
        {
            char buffer[1000];
            sscanf(buf, "%d %s", &x, buffer);
            int found = 0;
            for (int i = 1; i <= n; i++)
            {
                if (strcmp(strs[i], buffer) == 0 && !del[i])
                {
                    printf("True\n");
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
                printf("False\n");
            }
        }
    }
    return 0;
}