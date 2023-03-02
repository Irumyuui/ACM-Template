#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;

	vector<array<int,3>> edge(m);
	for (auto &&[u,v,w] : edge) {
		cin >> u >> v >> w;
	}
	sort(edge.begin(), edge.end(), [](const auto &a, const auto &b) {
		return a[2] < b[2];
	});

	vector<int> dad(n + 1, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1) {
			return x;
		}
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b) return false;
		dad[a] = b;
		return true;
	};

	int tot = 0;
	for (auto [u, v, w] : edge) {
		if (Merge(u, v)) {
			tot += w;
		}
	}

	if (count(dad.begin() + 1, dad.end(), -1) > 1) {
		cout << "orz\n";
	} else {
		cout << tot << '\n';
	}
}