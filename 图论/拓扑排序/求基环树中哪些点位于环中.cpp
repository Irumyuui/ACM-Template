#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n;
	cin >> n;

	vector adj(n + 1, vector<int>{});
	vector<int> deg(n + 1);
	for (int i = 1; i <= n; i ++) {
		int u, v;
		cin >> u >> v;
		deg[u] ++; deg[v] ++;
	}

	queue<int> q;
	for (int i = 1; i <= n; i ++) {
		if (deg[i] == 1) {
			q.emplace(i);
		}
	}
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (auto to : adj[from]) {
			if (deg[to] > 1) {
				deg[to] --;
				if (deg[to] == 1) {
					q.emplace(to);
				}
			}
		}
	}

	for (int i = 1; i <= n; i ++) {
		if (deg[i] != 1) {
			cout << i << " \n"[i == n];
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}