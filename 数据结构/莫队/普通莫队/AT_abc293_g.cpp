/**
 * https://atcoder.jp/contests/abc293/tasks/abc293_g
*/

#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
	for (int i = 0; i < q; i ++) {
		auto & [l, r, idx] = que[i];
		cin >> l >> r;
		idx = i;
	}
	sort(que.begin(), que.end(), [bk{int(sqrt(n))}](const auto &a, const auto &b) {
		if (a.l / bk != b.l / bk)
			return a.l < b.l;
		if (a.l / bk % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<i64> cnt(*max_element(a.begin() + 1, a.end()) + 1);
	i64 ret = 0;
	auto calc = [](i64 cnt) -> i64 {
		if (cnt < 3)
			return 0;
		return cnt * (cnt - 1) * (cnt - 2) / 6;
	};
	auto Add = [&](int pos) {
		ret -= calc(cnt[a[pos]]);
		cnt[a[pos]] ++;
		ret += calc(cnt[a[pos]]);
	};
	auto Del = [&](int pos) {
		ret -= calc(cnt[a[pos]]);
		cnt[a[pos]] --;
		ret += calc(cnt[a[pos]]);
	};

	vector<i64> ans(q);
	int L = 1, R = 0;
	for (auto [l, r, idx] : que) {
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