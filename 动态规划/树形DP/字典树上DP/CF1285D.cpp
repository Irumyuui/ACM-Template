#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	
	vector<array<int,3>> trie{{}};
	trie.reserve(int(1e6));
	auto Insert = [&](int x) {
		int p = 0;
		for (int i = 30; i >= 0; i --) {
			int d = (x >> i) & 1;
			if (trie[p][d] == 0) {
				trie[p][d] = trie.size();
				trie.push_back({});
			}
			p = trie[p][d];
			trie[p][2] ++;
		}
	};
	for (int i = 0; i < n; i ++) {
		int x;
		cin >> x;
		Insert(x);
	}

	auto dfs = [&](auto &&dfs, int now, int k) -> int {
		if (k < 0)
			return 0;
		if (!trie[now][0] && !trie[now][1]) {
			return 0;
		} else if (trie[now][0] && trie[now][1]) {
			return min({
				(1 << k) + dfs(dfs, trie[now][0], k - 1),
				(1 << k) + dfs(dfs, trie[now][1], k - 1),
			});
		} else if (trie[now][0]) {
			return dfs(dfs, trie[now][0], k - 1);
		} else {
			return dfs(dfs, trie[now][1], k - 1);
		}
	};
	cout << dfs(dfs, 0, 30) << '\n';
}