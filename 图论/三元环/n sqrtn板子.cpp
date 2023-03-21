#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

auto Solve() -> void {
	int n, m;
	cin >> n >> m;
	
	vector<pair<int,int>> edge(m);
	vector<int> deg(n);
	for (auto &[u,v] : edge) {
		cin >> u >> v;
		u --, v --;
		deg[u] ++, deg[v] ++;
	}

	vector g(n, vector<int>());
	for (auto [u,v] : edge) {
		if (deg[u] > deg[v]) {
			g[v].emplace_back(u);
		} else if (deg[u] < deg[v]) {
			g[u].emplace_back(v);
		} else {
			g[min(u,v)].emplace_back(max(u,v));
		}
	}

	ll ans = {};
	for (int i = 0; i < n; i ++) {
		vector<bool> tod(n);
		for (auto j : g[i])
			tod[j] = true;
		for (auto j : g[i])
			for (auto k : g[j]) 
				ans += tod[k];
	}
	cout << ans << '\n';
}

int main() {

}