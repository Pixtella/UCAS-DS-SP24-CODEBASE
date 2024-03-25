#include <stdio.h>
#include <ctype.h>
#include <math.h>
char S[10000];
int n, deg[10000], ans[10000];
int main()
{
    char ch;
    while((ch = getchar()) != EOF)
    {
        if (isdigit(ch) || isalpha(ch) || ch == '^' || ch == '+' || ch == '-')
        {
            S[n++] = ch;
        }
    }
    if (S[0] != '+' && S[0] != '-')
    {
        for (int i = n; i >= 0; i--)
            S[i + 1] = S[i];
        S[0] = '+';
        n++;
    }
    int i = 0;
    while (1)
    {
        int j = i + 1;
        int f;
        int is_const = 1;
        int x_pos;
        int ppow = 0;
        if (S[i] == '+') f = 1;
        else f = -1;
        while (S[j] != '+' && S[j] != '-' && j < n)
        {
            if (S[j] == 'x')
            {
                is_const = 0;
                x_pos = j;
            }
            j++;
        }
        if (is_const)
        {
            int val = 0;
            for (int k = i + 1; k < j; k++)
            {
                val = val * 10 + S[k] - '0';
            }
            deg[0] += val * f;
        }
        else
        {
            int coef = 0;
            for (int k = i + 1; k < x_pos; k++)
            {
                coef = coef * 10 + S[k] - '0';
            }
            if (S[x_pos + 1] == '^')
            {
                for (int k = x_pos + 2; k < j; k++)
                {
                    ppow = ppow * 10 + S[k] - '0';
                }
            }
            else
            {
                ppow = 1;
            }
            deg[ppow] += coef * f;
        }
        if (j == n) break;
        i = j;
    }
    for (int i = 1; i <= 1000; i++)
    {
        ans[i - 1] = deg[i] * i;
    }
    // print the result, printing the polynomial from the highest degree to the lowest
    int first = 1;
    for (int i = 1000; i >= 0; i--)
    {
        if (ans[i] != 0)
        {
            if (first)
            {
                first = 0;
                if (ans[i] < 0) printf("- ");
            }
            else
            {
                if (ans[i] > 0) printf(" + ");
                else printf(" - ");
            }
            if (i == 0 || ans[i] != 1 && ans[i] != -1)
            {
                printf("%d", abs(ans[i]));
            }
            if (i > 0)
            {
                printf("x");
                if (i > 1)
                {
                    printf("^%d", i);
                }
            }

        }
    }
    if (first) printf("0");
    printf("\n");
    return 0;
}