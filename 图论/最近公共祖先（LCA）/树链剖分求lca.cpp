#include <bits/stdc++.h>

const int N = 1e5 + 10;
std::vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].emplace_back(from);
	edge[to].emplace_back(from);
}

int dep[N], fa[N], siz[N], son[N], top[N], dfn[N], rnk[N], stamp = 0;

void build(int root) {
	static auto dfs1 = [&](auto &&dfs, int from) -> void {
		son[from] = -1;
		siz[from] = 1;
		for (auto to : edge[from]) 
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				fa[to] = from;
				dfs(dfs, to);
				if (son[from] == -1 || siz[to] > son[siz[from]]) son[from] = to;
			}
	};
	static auto dfs2 = [&](auto &&dfs, int from, int root) -> void {
		top[from] = root;
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		if (son[from] == -1) return;
		dfs(dfs, son[from], root);
		for (auto to : edge[from])
			if (to != fa[from] && to != son[from])
				dfs(dfs, to, to);		
	};

	memset(dep, -1, sizeof dep);
	dep[root] = stamp = 0;
	dfs1(dfs1, root);
	dfs2(dfs2, root, root);
}

int Lca(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]])
			std::swap(a, b);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b])
		std::swap(a, b);
	return a;
}