// abc296e
#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n;
	cin >> n;

	vector<int> a(n), ind(n);
	vector adj(n, vector<int>());
	for (int i = 0; i < n; i ++) {
		cin >> a[i];
		a[i] --;
		adj[i].emplace_back(a[i]);
		ind[a[i]] ++;
	}

	queue<int> q;
	for (int i = 0; i < n; i ++) {
		if (ind[i] == 0) {
			q.emplace(i);
		}
	}
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (auto to : adj[from]) {
			if (-- ind[to] == 0) {
				q.emplace(to);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i ++) {
		ans += ind[i] != 0;
	}
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}