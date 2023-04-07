#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n;
	cin >> n;

	vector adj(n + 1, vector<pair<int,int>>());
	for (int i = 0; i < n - 1; i ++) {
		int from, to;
		cin >> from >> to;
		adj[from].emplace_back(to, 1);
		adj[to].emplace_back(from, 0);
	}

	vector<int> dep(n + 1, -1);
	queue<int> q;
	dep[1] = 1;
	q.emplace(1);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (auto [to, w] : adj[from]) {
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				q.emplace(to);
			}
		}	
	}

	vector<int> f(n + 1);
	auto dfs1 = [&](auto &&dfs, int from) -> void {
		for (auto [to, dre] : adj[from]) {
			if (dep[to] == dep[from] + 1) {
				dfs(dfs, to);
				f[from] += f[to] + (dre == 0);
			}
		}
	};
	dfs1(dfs1, 1);

	vector<int> rf(n + 1);
	auto dfs2 = [&](auto &&dfs, int from, int come, int come_dre) -> void {
		if (come != -1) {
			if (come_dre) {
				rf[from] = f[come] - f[from] + 1 + rf[come];
			} else {
				rf[from] = f[come] - f[from] - 1 + rf[come];
			}
		}
		for (auto [to, dre] : adj[from]) {
			if (dep[to] == dep[from] + 1) {
				dfs(dfs, to, from, dre);
			}
		}
	};
	dfs2(dfs2, 1, -1, 0);

	vector<pair<int,int>> ret(n);
	for (int i = 1; i <= n; i ++) {
		ret[i - 1] = {(f[i] + rf[i]), i};
	}
	ranges::sort(ret);
	while (ret.back().first != ret.front().first) {
		ret.pop_back();
	}
	cout << ret.front().first << '\n';
	for (auto [i, k] : ret) {
		cout << k << ' ';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	Main();
}