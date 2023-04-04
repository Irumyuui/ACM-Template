// 2020 CCPC Henan Provincial Collegiate Programming Contest J

#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

void Main() {
	int n, m;
	cin >> n >> m;

	vector<array<i64,2>> a(n);
	for (int i = 0; i < n; i ++) 
		cin >> a[i][0];
	for (int i = 0; i < n; i ++)
		cin >> a[i][1];
	vector<pair<int,int>> edge(m);
	for (auto &[u, v] : edge) {
		cin >> u >> v;
		u --; v --;
	}

	auto check = [&](i64 tag) -> bool {
		vector adj(n * 2, vector<int>());
		for (auto [u, v] : edge)
			for (int i : {0, 1})
				for (int j : {0, 1})
					if (abs(a[u][i] - a[v][j]) > tag) {
						adj[u * 2 + i].emplace_back((v * 2 + j) ^ 1);
						adj[v * 2 + j].emplace_back((u * 2 + i) ^ 1);
					}

		vector<int> dfn(n * 2, -1), low(n * 2, -1), scc_id(n * 2, -1), stk;
		vector<bool> inst(n * 2);
		int stamp = 0, scc_cnt = 0;
		auto dfs = [&](auto &&dfs, int from) -> void {
			dfn[from] = low[from] = ++ stamp;
			inst[from] = true;
			stk.emplace_back(from);
			for (auto to : adj[from]) 
				if (dfn[to] == -1) {
					dfs(dfs, to);
					low[from] = min(low[from], low[to]);
				} else if (inst[to]) {
					low[from] = min(low[from], dfn[to]);
				}
			if (low[from] == dfn[from]) {
				int now = 0;
				do {
					now = stk.back();
					stk.pop_back();
					inst[now] = false;
					scc_id[now] = scc_cnt;
				} while (now != from);
				scc_cnt ++;
			}
		};
		for (int i = 0; i < n * 2; i ++) 
			if (dfn[i] == -1) 
				dfs(dfs, i);
		
		for (int i = 0; i < n * 2; i += 2) 
			if (scc_id[i] == scc_id[i + 1])
				return false;
		return true;
	};

	i64 l = 0, r = inf<i64>, ans = -1;
	while (l <= r) {
		i64 mid = l + ((r - l) >> 1);
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}