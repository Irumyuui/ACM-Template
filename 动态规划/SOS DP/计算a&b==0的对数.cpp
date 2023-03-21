// https://ac.nowcoder.com/acm/problem/249647

#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> a(n);
	vector<ll> f((1 << 22), 0);
	for (auto &x : a) {
		cin >> x;
		f[x] ++;
	}

	for (int bit = 1; bit < 22; bit ++) {
		for (int i = (1 << 22) - 1; i >= 0; i --) {
			if (i & (1 << bit)) {
				f[i] += f[i ^ (1 << bit)];
			}
		}
	}

	ll ans = 0;
	for (auto x : a) {
		ans += f[x ^ ((1 << 22) - 1)];
	}
}