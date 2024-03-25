#include <stdio.h>
#define maxn 1000
int n,m,mp[maxn][maxn],sx,sy;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void DFS(int x, int y)
{
    int c = mp[x][y];
    mp[x][y] = 2;
    if(x-1>=1 && mp[x-1][y] == c) DFS(x-1,y);
    if(x+1<=n && mp[x+1][y] == c) DFS(x+1,y);
    if(y-1>=1 && mp[x][y-1] == c) DFS(x,y-1);
    if(y+1<=m && mp[x][y+1] == c) DFS(x,y+1);
}
int main()
{
    n=read();m=read();
    sx=read();sy=read();
    read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            mp[i][j]=read();
    DFS(sx,sy);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            printf("%d",mp[i][j]);
        printf("\n");
    }
    return 0;
}