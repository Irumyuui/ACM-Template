/**
 * https://atcoder.jp/contests/abc242/tasks/abc242_g
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

using i64 = std::int64_t;

void Main() {
	int n;
	cin >> n;
	
	vector<int> a(n + 1);
	for (int i =  1; i <= n; i ++) {
		cin >> a[i];
	}
	
	int q;
	cin >> q;
	struct Query_Seg {
		int l, r, idx;
	};
	vector<Query_Seg> que(q);
	for (int i = 0; i < q; i ++) {
		auto &[l, r, idx] = que[i];
		cin >> l >> r;
		idx = i;
	}
	sort(que.begin(), que.end(), [block{int(sqrt(n))}](const auto &a, const auto &b) {
		if (a.l / block != b.l / block) 
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<int> cnt(*max_element(a.begin() + 1, a.end()) + 1);
	int ret = 0;
	auto Add = [&](int pos) {
		cnt[a[pos]] ++;
		ret += cnt[a[pos]] % 2 == 0;
	};
	auto Del = [&](int pos) {
		ret -= cnt[a[pos]] % 2 == 0;
		cnt[a[pos]] --;
	};
	
	vector<int> ans(q);
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