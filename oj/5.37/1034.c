#include <stdio.h>
#include <string.h>
char S[10000];char x;
int main()
{
    scanf("%s %c",S, &x);
    for (int _ = 0; _ < 1000; _++)
    {
        int pos, len = 0;
        int n = strlen(S);
        for (int i = 0; i < n; i++)
        {
            if (S[i] == x)
            {
                pos = i;
                len = 1;
                break;
            }
            else if (i && S[i] == ',' && (S[i - 1] == '(' || S[i - 1] == ',' || S[i + 1] == ')'))
            {
                pos = i;
                len = 1;
                break;
            }
            else if (S[i] == '(' && S[i + 1] == ')')
            {
                pos = i;
                len = 2;
                break;
            }
        }
        if (len == 0)
            break;
        for (int i = pos + len; i < n; i++)
            S[i - len] = S[i];
        S[n - len] = 0;
    }
    if (S[0] == 0)
        printf("-1");
    else
        printf("%s", S);
    return 0;
}