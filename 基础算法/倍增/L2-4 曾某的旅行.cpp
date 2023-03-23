// https://pintia.cn/problem-sets/1638481503132475392/exam/problems/1638481528990367755

#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, m, q;
	cin >> n >> m >> q;
	
	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= n; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
	}

	vector f(31, vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		if (adj[i].empty()) {
			f[0][i] = i;
		} else {
			for (auto j : adj[i]) {
				f[0][i] = j;
			}
		}
	}
	for (int i = 1; i <= 30; i ++) {
		for (int j = 1; j <= n; j ++) {
			f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}

	for (int _ = 1; _ <= q; _ ++) {
		int x, k;
		cin >> x >> k;
		for (int i = 30; i >= 0; i --) {
			if (k >= (1 << i)) {
				k -= 1 << i;
				x = f[i][x];
			}
		}
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}