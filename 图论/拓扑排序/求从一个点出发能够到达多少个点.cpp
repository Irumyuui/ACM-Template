#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;
	std::vector rg(n, std::vector<int>());  // 反图
	std::vector<int> ind(n);
	for (int i = 0; i < m; i ++) {
		int u, v;
		std::cin >> u >> v;
		u --; v --;
		rg[v].emplace_back(u);
		ind[u] ++;
	}

	std::vector<std::bitset<3000>> cnt(n);
	std::vector<int> q;
	q.reserve(n);
	for (int i = 0; i < n; i ++) {
		if (!ind[i]) q.emplace_back(i);
		cnt[i][i] = 1;
	}
	for (int i = 0; i < n; i ++) {
		int from = q[i];
		for (auto to : rg[from]) {
			cnt[to] |= cnt[from];
			if (-- ind[to] == 0) 
				q.emplace_back(to);
		}
	}

	for (int i = 0; i < n; i ++) 
		std::cout << cnt[i].count() << '\n';
}