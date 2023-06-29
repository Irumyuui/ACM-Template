#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n;
	cin >> n;
	vector<i64> a(n);
	for (auto &x : a) cin >> x;
	i64 tmp = 0, ans = 0;
	for (auto x : a) {
		tmp += x;
		if (tmp < 0) tmp = 0;
		ans = max(ans, tmp);
	}
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}