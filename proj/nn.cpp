#include <bits/stdc++.h>
using namespace std;
const int board_size = 20;
const int dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};
int neuron_num, sx, sy;
int ord[board_size][board_size];
struct Neuron
{
    int from;
    int to;
    vector<int> neighbors;
}nn[board_size * board_size * 8];
int U[2][board_size * board_size * 8], V[2][board_size * board_size * 8];
void id2coord(int id, int& x, int& y)
{
    x = id / board_size;
    y = id % board_size;
}
int coord2id(int x, int y)
{
    return x * board_size + y;
}
void init(int idx)
{
    for (int i = 0; i < neuron_num; i++)
    {
        U[idx][i] = rand() % board_size;
        V[idx][i] = 0;
    }
}
int tot, lnk[board_size * board_size + 5], nxt[board_size * board_size * 2 + 5], son[board_size * board_size * 2 + 5], deg[board_size * board_size + 5];
void add_e(int x, int y)
{
    tot++;
    son[tot] = y;
    nxt[tot] = lnk[x];
    lnk[x] = tot;
    deg[y]++;
}
bool check_ans()
{
    tot = 0;
    memset(lnk, 0, sizeof(lnk));
    memset(deg, 0, sizeof(deg));
    for (int i = 0; i < neuron_num; i++)
    {
        if (V[0][i] == 1)
        {
            add_e(nn[i].from, nn[i].to);
            add_e(nn[i].to, nn[i].from);
        }
    }
    for (int i = 0; i < board_size * board_size; i++)
    {
        if (deg[i] != 2)
            return false;
    }
    bool vis[board_size * board_size] = {false};
    int p = coord2id(sx, sy);
    for (int i = 0; i < board_size * board_size; i++)
    {
        int x, y;
        id2coord(p, x, y);
        ord[x][y] = i;
        if (vis[p])
            return false;
        vis[p] = true;
        if (vis[son[lnk[p]]])
            p = son[nxt[lnk[p]]];
        else
            p = son[lnk[p]];
    }
    return true;
}
int main()
{
    for (int f = 0; f < board_size * board_size; f++)
    {
        int fx, fy;
        id2coord(f, fx, fy);
        for (int i = 0; i < 8; i++)
        {
            int tx = fx + dir[i][0], ty = fy + dir[i][1];
            if (tx < 0 || ty < 0 || tx >= board_size || ty >= board_size)
                continue;
            int t = coord2id(tx, ty);
            if (t < f)
                continue;
            nn[neuron_num].from = f;
            nn[neuron_num].to = t;
            neuron_num++;
        }
    }
    for (int i = 0; i < neuron_num; i++)
    {
        for (int j = 0; j < neuron_num; j++)
        {
            if (i == j)
                continue;
            if (nn[j].from == nn[i].to || nn[j].from == nn[i].from || nn[j].to == nn[i].to || nn[j].to == nn[i].from)
                nn[i].neighbors.push_back(j);
        }
    }
    init(0);
    for (int t = 1; ;t++)
    {
        int idx = t & 1;
        int pre = idx ^ 1;
        bool converged = true;
        for (int i = 0; i < neuron_num; i++)
        {
            int sum = 0;
            for (auto j : nn[i].neighbors)
            {
                sum += V[pre][j];
            }
            U[idx][i] = U[pre][i] + 4 - sum;
            if (V[pre][i] == 1)
                U[idx][i] -= 2;
            if (U[idx][i] != U[pre][i])
                converged = false;
            V[idx][i] = (U[idx][i] > 3) ? 1 : ((U[idx][i] < 0) ? 0 : V[pre][i]);
        }
        if (converged) // Converged
        {
            printf("Converged at %d\n", t);
            if (check_ans())
            {
                break;
            }
            else
            {
                printf("Failed\n");
                init(idx);
            }
        }
        if (t > 1000)
        {
            printf("Divergent!\n");
            init(0);
            t = 0;
        }
    }
    for (int i = 0; i < board_size; i++, puts(""))
        for (int j = 0; j < board_size; j++)
            printf("|%d\t", ord[i][j]);
    return 0;
}