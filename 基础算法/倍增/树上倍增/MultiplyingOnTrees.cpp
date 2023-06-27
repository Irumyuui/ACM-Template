#include <bits/stdc++.h>
using namespace std;

// 树上倍增
class MultiplyingOnTree {
public:
	MultiplyingOnTree(int size, int root)
		: adj(size + 1), fa(std::__lg(size) + 1, std::vector<int>(size + 1)), dep(size + 1, -1), n(size), root(root) {}

	void AddEdge(int u, int v) {
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	void Build() {
		auto dfs = [&](auto &&dfs, int from, int come) -> void {
			dep[from] = come;
			fa[0][from] = come;
			for (int i = 1; i <= std::__lg(dep[from]); i ++)
				fa[i][from] = fa[i - 1][fa[i - 1][from]];
			for (auto to : adj[from]) 
				if (to != come)
					dfs(dfs, to, from);
		};
		dep[0] = 0;
		dfs(dfs, root, 0);
	}

	int GetLca(int a, int b) {
		if (dep[a] > dep[b]) 
			std::swap(a, b);
		while (dep[a] != dep[b])
			a = fa[std::__lg(dep[a] - dep[b])][a];
		if (a == b)
			return a;
		for (int i = std::__lg(dep[a]); i >= 0; i --) {
			if (fa[i][a] != fa[i][b]) {
				a = fa[i][a];
				b = fa[i][b];
			}
		}
		return fa[0][a];
	}

	int GetKthFather(int x, int kth) {
		int targetDeep = dep[x] - kth;
		for (int i = std::__lg(n); i >= 0; i --) {
			if (dep[fa[i][x]] >= targetDeep) {
				x = fa[i][x];
			}
		}
		return x;
	}

private:
	std::vector<std::vector<int>> adj, fa;
	std::vector<int> dep;
	int n, root;
};