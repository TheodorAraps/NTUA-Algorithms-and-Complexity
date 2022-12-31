#include <cstdio>
#include <algorithm>
#include <vector>

int N, M, Q, parent[50001], Rank[50001], depth[50001], path[50001][17], rmq[50001][17], Answer[100000];
std::pair<int, std::pair<int, int>> edges[100000];
std::vector<std::pair<int, int>> tree[50001];

int find(int v)
{
	if (parent[v] == v) return v;
	return parent[v] = find(parent[v]);
}

void Union(int v, int u)
{
	v = find(v);
	u = find(u);
	if (Rank[u] < Rank[v])
	{
		parent[u] = v;
	}
	else
	{
		parent[v] = u;
		if (Rank[v] == Rank[u]) Rank[u]++;
	}
}

void DFS(int v, int p)
{
	path[v][0] = p;
	for (int i = 0; i < tree[v].size(); i++)
	{
		int x = tree[v][i].first, y = tree[v][i].second;
		if (x == p) continue;
		rmq[x][0] = y;
		depth[x] = depth[v] + 1;
		DFS(x, v);
	}
}

int lca(int u, int v)
{
	int k = 0;

	if (depth[u] < depth[v]) std::swap(u, v);

	if (!depth[u]) return u;

	for (k = 0; 1 << k <= depth[u]; k++);
	k--;

	for (int i = k; i >= 0; i--)
	{
		if (depth[u] - (1 << i) >= depth[v]) u = path[u][i];
	}

	if (u == v) return u;

	for (int i = k; i >= 0; i--)
	{
		if (path[u][i] != -1 && path[u][i] != path[v][i])
		{
			u = path[u][i];
			v = path[v][i];
		}
	}

	return path[u][0];
}

int answer(int u, int v)
{
	int lca_ret = lca(u, v), m_i = 0, uu_i, uv_i;

	for (uu_i = 0; 1 << uu_i <= depth[u]; uu_i++);
	uu_i--;

	for (uv_i = 0; 1 << uv_i <= depth[v]; uv_i++);
	uv_i--;


	if (!depth[u] && !depth[v]) return 0;

	for (int i = uu_i; i >= 0; i--)
	{
		if (depth[u] - (1 << i) >= depth[lca_ret])
		{
			m_i = std::max(m_i, rmq[u][i]);
			u = path[u][i];
		}
	}
	for (int i = uv_i; i >= 0; i--)
	{
		if (depth[v] - (1 << i) >= depth[lca_ret])
		{
			m_i = std::max(m_i, rmq[v][i]);
			v = path[v][i];
		}
	}

	return m_i;
}

int main(void)
{
	int x, y, d;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) parent[i] = i;

	for (int i = 0; i < M; i++)
	{
		scanf("%d%d%d", &x, &y, &d);
		edges[i] = std::make_pair(d, std::make_pair(x, y));
	}

	sort(edges, edges + M);

	for (int i = 0; i < M; i++)
	{
		x = edges[i].second.first;
		y = edges[i].second.second;
		d = edges[i].first;
		if (find(x) != find(y))
		{
			Union(x, y);
			tree[x].push_back(std::make_pair(y, d));
			tree[y].push_back(std::make_pair(x, d));
		}
	}

	DFS(1, -1);

	for (int i = 1; (1 << i) <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			path[j][i] = path[path[j][i - 1]][i - 1];
			rmq[j][i] = std::max(rmq[path[j][i - 1]][i - 1], rmq[j][i - 1]);
		}
	}

	scanf("%d", &Q);
	for (int i = 0; i < Q; i++)
	{
		scanf("%d%d", &x, &y);
		Answer[i] = answer(x, y);
	}
	for (int i = 0; i < Q; i++)
	{
		printf("%d\n", Answer[i]);
	}
}