#include <stdio.h>
int sc[5][2];
char GetC()
{
    char ch = getchar();
    while (ch < 'A' || ch > 'Z')
    {
        if (ch == EOF)
            return ch;
        ch = getchar();
    }
    return ch;
}
int read()
{
    int ret = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == EOF)
            return -1;  
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + ch - '0';
        ch = getchar();
    }
    return ret * f;
}
int main()
{
    while (1)
    {
        char p = GetC();
        if (p == EOF)
            break;
        char gen = GetC();
        char sch = GetC();
        int scr = read();
        gen = (gen == 'M' ? 0 : 1);
        sch = (sch - 'A');
        sc[sch][gen] += scr;
    }
    for (int sch = 0; sch < 5; sch++)
    {
        if (sc[sch][0])
            printf("%c M %d\n", sch + 'A', sc[sch][0]);
        if (sc[sch][1])
            printf("%c F %d\n", sch + 'A', sc[sch][1]);
        if (sc[sch][0] || sc[sch][1])
            printf("%c %d\n", sch + 'A', sc[sch][0] + sc[sch][1]);
    }
    return 0;
}