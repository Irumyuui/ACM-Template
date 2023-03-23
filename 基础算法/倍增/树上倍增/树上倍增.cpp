#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n;
	cin >> n;

	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	vector fa(__lg(n) + 1, vector<int>(n + 1));
	auto dfs = [&](auto &&dfs, int from, int come) -> void {
		f[0][from] = come;
		for (int i = 1; i <= __lg(n); i ++) {
			f[i][from] = f[i - 1][f[i - 1][from]];
		}		
		for (auto to : adj[from]) {
			if (to != come) {
				dfs(dfs, to, from);
			}
		}
	};
}

int main() {
	
}