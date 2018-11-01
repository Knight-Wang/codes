#include <bits/stdc++.h>

#define N (1005)
#define M (N * N + 4 * N)
const int INF = 0x3f3f3f3f;
typedef long long LL;

using namespace std;

struct edge 
{
    int v, cap, next;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

void dinic_init(void) 
{
    num_of_edges = 0;
    memset(head, -1, sizeof(head));
    return;
}

int add_edge(int u, int v, int c1, int c2) 
{
    int& i = num_of_edges;

    assert(c1 >= 0 && c2 >= 0 && c1 + c2 >= 0); // check for possibility of overflow
    e[i].v = v;
    e[i].cap = c1;
    e[i].next = head[u];
    head[u] = i++;

    e[i].v = u;
    e[i].cap = c2;
    e[i].next = head[v];
    head[v] = i++;
    return i;
}

int dfs(int u, int t, int bn) 
{
    if (u == t) return bn;
    int left = bn;
    for (int &i = cur[u]; i >= 0; i = e[i].next) 
    {
        int v = e[i].v;
        int c = e[i].cap;
        if (c > 0 && level[u] + 1 == level[v]) 
        {
            int flow = dfs(v, t, min(left, c));
            if (flow > 0) 
            {
                e[i].cap -= flow;
                e[i ^ 1].cap += flow;
                cur[u] = i;
                left -= flow;
                if (!left) break;
            }
        }
    }
    if (left > 0) level[u] = 0;
    return bn - left;
}

bool bfs(int s, int t) 
{
    memset(level, 0, sizeof(level));
    level[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        if (u == t) return true;
        for (int i = head[u]; i >= 0; i = e[i].next) 
        {
            int v = e[i].v;
            if (!level[v] && e[i].cap > 0) 
            {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}

LL dinic(int s, int t) 
{
    LL max_flow = 0;

    while (bfs(s, t)) 
    {
        memcpy(cur, head, sizeof(head));
        max_flow += dfs(s, t, INT_MAX);
    }
    return max_flow;
}

int main()
{
    int n, m, x, y;
    while (cin >> n >> m)
    {
        dinic_init();
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y;
            add_edge(x, n + y, 1, 0);
        }
        for (int i = 1; i <= n; i++)
            add_edge(0, i, 1, 0);
        for (int i = 1; i <= n; i++)
            add_edge(i + n, 2 * n + 1, 1, 0);
        cout << n - dinic(0, 2 * n + 1) << endl;
    }
    return 0;
}