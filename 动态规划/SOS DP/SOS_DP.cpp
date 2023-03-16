#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> a(n), f(1 << 22);
	for (auto &x : a) {
		cin >> x;
		f[x] ++;
	}
	for (int mask = 0; mask < 21; mask ++) {
		for (int i = 0; i < (1 << 21); i ++) {
			if (i & (1 << mask)) {
				f[i] += f[i ^ (1 << mask)];
			}
		}
	}
}