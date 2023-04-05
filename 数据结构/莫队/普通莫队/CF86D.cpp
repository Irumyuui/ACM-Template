/**
 * https://codeforces.com/contest/86/problem/D
*/

#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n, q;
	cin >> n >> q;
	
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	
	struct Query {
		int l, r, idx;
	};
	vector<Query> que(q);
	for (int t = 0; auto &[l, r, idx] : que) {
		cin >> l >> r;
		idx = t ++;
	}
	ranges::sort(que, [block{int(sqrt(n))}](const Query &a, const Query &b) -> bool {
		if (a.l / block != b.l / block)
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<i64> cnt(ranges::max(a) + 1);
	i64 ret = 0;
	auto Add = [&](int p) {
		ret -= cnt[a[p]] * cnt[a[p]] * a[p];
		cnt[a[p]] ++;
		ret += cnt[a[p]] * cnt[a[p]] * a[p];
	};
	auto Del = [&](int p) {
		ret -= cnt[a[p]] * cnt[a[p]] * a[p];
		cnt[a[p]] --;
		ret += cnt[a[p]] * cnt[a[p]] * a[p];
	};

	vector<i64> ans(q);
	int L = 1, R = 0;
	for (const auto [l, r, idx] : que) {
		while (L > l) 
			Add(-- L);
		while (R < r) 
			Add(++ R);
		while (L < l)
			Del(L ++);
		while (R > r) 
			Del(R --);
		ans[idx] = ret;
	}

	for (auto x : ans) {
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}