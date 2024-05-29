#include <stdio.h>
int EOF_flag;
int a[1000]; int n;
int read()
{
    int ret = 0, f = 1;char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == EOF) {EOF_flag = 1;return 0;}if (ch == '-') f = -1;ch = getchar();}
    while (ch >= '0' && ch <= '9') {ret = ret * 10 + ch - '0';ch = getchar();}
    return ret * f;
}
int sort(int l, int r)
{
    int i = l, j = r, mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j)
        {
            int t = a[i]; a[i] = a[j]; a[j] = t;
            i++; j--;
        }
    }
    if (l < j) sort(l, j);
    if (i < r) sort(i, r);
}
int main()
{
    while (!EOF_flag)
    {
        int x = read();
        if (EOF_flag) break;
        if (x != -1)
        a[++n] = x;
    }
    sort(1, n);
    for (int i = 1; i <= n; i++)
        printf("%d%c", a[i], i == n ? '\n' : ' ');
    return 0;
}