#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

constexpr auto solve(ll first, ll last, ll n) -> ll {
	ll ans = 0;
	for (ll l = first; l <= last; ) {
		ll r = n / (n / l);
		ans += (r - l + 1) * (n / l);
		l = r + 1;
	}
	return ans;
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		ll l, r, n;
		cin >> l >> r >> n;
		cout << solve(l, r, n) << '\n';
	}
}