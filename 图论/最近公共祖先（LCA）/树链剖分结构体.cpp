#include <bits/stdc++.h>

struct LowestCommonAncestorGraph {	
	explicit LowestCommonAncestorGraph(int _n) 
		: adj(_n), dfn(_n + 1, -1), rnk(_n + 1, -1),
	      fa(_n, -1), top(_n, -1), dep(_n, -1), son(_n, -1), siz(_n, -1) {}

	void AddDirectedEdge(int from, int to) {
		adj[from].emplace_back(to);
	}
	void AddUndirectedEdge(int u, int v) {
		AddDirectedEdge(u, v);
		AddDirectedEdge(v, u);
	}

	void Assign(int n) {
		adj.assign(n, {});
		dfn.assign(n + 1, -1);
		rnk.assign(n + 1, -1);
		fa.assign(n, -1);
		top.assign(n, -1);
		dep.assign(n, -1);
		son.assign(n, -1);
		siz.assign(n, -1);
	}

	void Init() {
		std::fill(std::begin(dep), std::end(dep), -1);
		std::fill(std::begin(fa), std::end(fa), -1);
	}

	void Build(int root, int stamp = 1) {
		auto dfs1 = [&](auto &&dfs, int from) -> void {
			son[from] = -1;
			siz[from] = 1;
			for (auto to : adj[from]) {
				if (dep[to] == -1) {
					dep[to] = dep[from] + 1;
					fa[to] = from;
					dfs(dfs, to);
					siz[from] += siz[to];
					if (son[from] == -1 || siz[to] > siz[son[from]]) {
						son[from] = to;
					}
				}	
			}
		};
		auto dfs2 = [&](auto &&dfs, int from, int root) -> void {
			top[from] = root;
			dfn[from] = ++ stamp;
			rnk[stamp] = from;
			if (son[from] == -1) {
				return;
			}
			dfs(dfs, son[from], root);
			for (auto to : adj[from]) {
				if (to != son[from] && to != fa[from]) {
					dfs(dfs, to, to);
				}
			}
		};
		dep[root] = 0;
		dfs1(dfs1, root);
		dfs2(dfs2, root, root);
	}

	int GetLowestCommonAncestor(int a, int b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				std::swap(a, b);
			}
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			std::swap(a, b);
		}
		return a;
	}

	auto& operator [] (int idx) {
		return adj[idx];
	}
	auto& operator [] (int idx) const {
		return adj[idx];
	}

	std::vector<std::vector<int>> adj;
	std::vector<int> dfn, rnk, fa, top, dep, son, siz;
};