#include <stdio.h>
int in_s[200], in_t[200], fst[200];
char S[200], T[200];
int main()
{
    scanf("%s", S);
    scanf("%s", T);
    for (int i = 0; S[i] != '\0'; i++)
    {
        if (!in_s[S[i]])
        {
            in_s[S[i]] = 1;
            fst[S[i]] = i;
        }
    }
    for (int i = 0; T[i] != '\0'; i++)
    {
        if (!in_t[T[i]])
        {
            in_t[T[i]] = 1;
        }
    }
    int out = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (in_s[i] && !in_t[i])
        {
            out = 1;
            putchar(i);
        }
    }
    if(out)
    {
        putchar(' ');
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (in_s[i] && !in_t[i])
        {
            printf("%d", fst[i]);
        }
    }
    if (!out)
    {
        printf("-1");
    }
    return 0;
}