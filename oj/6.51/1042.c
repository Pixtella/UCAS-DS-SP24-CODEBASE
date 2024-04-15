#include <stdio.h>
char buf[100];
char ch[1000];
int left[1000], right[1000];
int p;
int cnt = 1;
void DFS(int x)
{
    ch[x] = buf[p++];
    if (!buf[p]) return;
    if (buf[p] == '#')
    {
        p += 2;
        return;
    }
    cnt++;
    left[x] = cnt;
    DFS(left[x]);
    cnt++;
    right[x] = cnt;
    DFS(right[x]);
}
void printdfs(int x, int lb)
{
    if (!left[x] && !right[x])
    {
        while(lb--) printf("(");
        printf("%c", ch[x]);
        return;
    }
    int dlb = 0;
    if (left[x] && (ch[x] == '*' || ch[x] == '/' || ch[x] == '\\') && (ch[left[x]] == '+' || ch[left[x]] == '-')) dlb = 1;
    printdfs(left[x], lb + dlb);
    if (dlb) printf(")");
    printf("%c", ch[x]);
    dlb = 0;
    if (right[x] && (ch[x] == '*' || ch[x] == '/' || ch[x] == '\\') && (ch[right[x]] == '+' || ch[right[x]] == '-')) dlb = 1;
    if (right[x] && ch[x] == '-' && (ch[right[x]] == '+' || ch[right[x]] == '-')) dlb = 1;
    if (dlb) printf("(");
    printdfs(right[x], 0);
    if (dlb) printf(")");
}
int main()
{
    gets(buf);
    DFS(1);
    printdfs(1, 0);
    return 0;
}