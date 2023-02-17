#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 2e5 + 10;
struct Info {
	int val;
	bool ok;
	friend Info operator + (const Info &a, const Info &b) {
		return {0, a.ok && b.ok};
	}
};
struct Node {
	Info val;
} seg[N * 4];

int a[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id) {
	seg[id].val.ok = false;
	if (l == r) {
		seg[id].val.val = a[l];
		seg[id].val.ok = false;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void modify(int l, int r, int id, int ml, int mr) {
	if (seg[id].val.ok) 
		return;
	if (l == ml && r == mr) {
		if (l == r) {
			int tmp = seg[id].val.val;
			int ret = 0;
			while (tmp > 0) {
				ret += tmp % 10;
				tmp /= 10;
			}
			if (ret == seg[id].val.val) {
				seg[id].val.ok = true;
			} else {
				seg[id].val.val = ret;
			}
		} else {
			int mid = l + ((r - l) >> 1);
			if (!seg[id * 2].val.ok)
				modify(l, mid, id * 2, ml, mid);
			if (!seg[id * 2 + 1].val.ok) 
				modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
			rise(id);
		}
		return;
	}

	int mid = l + ((r - l) >> 1);
	if (mr <= mid) {
		modify(l, mid, id * 2, ml, mr);
 	} else if (ml > mid) {
		modify(mid + 1, r, id * 2 + 1, ml, mr);
	} else {
		modify(l, mid, id * 2, ml, mid);
		modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
	}
	rise(id);
}

Info query(int l, int r, int id, int tag) {
	if (l == r) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) 
			return query(l, mid, id * 2, tag);
		return query(mid + 1, r, id * 2 + 1, tag);		
	}
}

auto Solve() -> void {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	build(1, n, 1);

	while (q --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int l, r;
			cin >> l >> r;
			modify(1, n, 1, l, r);
		} else {
			int x;
			cin >> x;
			cout << query(1, n, 1, x).val << '\n';
		}
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}