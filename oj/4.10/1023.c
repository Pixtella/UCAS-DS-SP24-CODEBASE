#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char S[10000005];
void str_rev(char* Str)
{
    int i, j;
    char temp;
    for (i = 0, j = strlen(Str) - 1; i < j; i++, j--)
    {
        temp = Str[i];
        Str[i] = Str[j];
        Str[j] = temp;
    }
}
int main()
{
    char ch = getchar();
    int n = 0;
    while (ch != '\n' && ch != EOF)
    {
        S[n++] = ch;
        ch = getchar();
    }
    str_rev(S);
    printf("%s", S);
    return 0;
}