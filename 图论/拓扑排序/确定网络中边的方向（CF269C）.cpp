#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

void Main() {
	int n, m;
	cin >> n >> m;
	vector adj(n + 1, vector<tuple<int,int,int,ll>>()); // 下一个点 边id 相较于输入的方向 流量
	vector<ll> ind(n + 1);
	for (int i = 0; i < m; i ++) {
		int u, v, cap;
		cin >> u >> v >> cap;
		adj[u].emplace_back(v, i, 0, cap);
		adj[v].emplace_back(u, i, 1, cap);
		ind[u] += cap; ind[v] += cap;
	}

	// 非源点 非汇点 的点其入流为所有边的流量和一半
	for (int i = 2; i < n; i ++) {
		ind[i] /= 2;
	}

	vector<int> ans(m, -1);
	queue<int> q;
	q.emplace(1);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (auto [to, eid, d, cap] : adj[from]) {
			// 边方向未确定 流量够入
			if (ans[eid] == -1 && ind[to] >= cap) {
				ans[eid] = d;
				ind[to] -= cap;
				if (ind[to] == 0) {
					q.emplace(to);
				}
			}
		}
	}

	for (int i : ans) {
		cout << i << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}