#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAXV = 403, INF = 0x3f3f3f3f;
struct edge
{
	int to, cap, rev;
	edge(int t, int c, int r) { to = t; cap = c; rev = r; }
};
int level[MAXV];
int iter[MAXV];
vector<edge> G[MAXV];
int n, f, d;
void add_edge(int from, int to, int cap)
{
	edge e(to, cap, G[to].size());
	G[from].push_back(e);
	edge er(from, 0, G[from].size() - 1);
	G[to].push_back(er);
}
void bfs(int s)
{
	memset(level, -1, sizeof level);
	queue<int> q;
	level[s] = 0;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front(); q.pop();
		for (int i = 0; i < G[v].size(); i++)
		{
			edge& e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0)
			{
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}
int dfs(int v, int t, int f)
{
	if (v == t) return f;
	for (int& i = iter[v]; i < G[v].size(); i++)
	{
		edge& e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s, int t)
{
	int flow = 0;
	for (;;)
	{
		bfs(s);
		if (level[t] < 0) return flow;
		memset(iter, 0, sizeof iter);
		int f = 0;
		while ((f = dfs(s, t, INF)) > 0)
			flow += f;
	}
}

int main()
{
	cin >> n >> f >> d;
	for (int i = 1; i <= n; i++)
	{
		int t1, t2, x;
		cin >> t1 >> t2;
		for (int j = 1; j <= t1; j++)
		{
			cin >> x; add_edge(x, f + i, 1);
		}
		for (int j = 1; j <= t2; j++)
		{
			cin >> x; add_edge(f + n + i, f + 2 * n + x, 1);
		}
	}
	for (int i = 1; i <= f; i++) add_edge(0, i, 1);
	for (int i = 1; i <= d; i++) add_edge(f + 2 * n + i, f + 2 * n + d + 1, 1);
	for (int i = 1; i <= n; i++) add_edge(f + i, f + n + i, 1);
	cout << max_flow(0, f + 2 * n + d + 1) << endl;
	return 0;
}