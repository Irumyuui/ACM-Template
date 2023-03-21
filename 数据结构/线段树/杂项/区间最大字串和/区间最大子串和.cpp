#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

const int N = 2e5 + 10;

struct Info {
	ll val, pre, suf, max_val;
	Info(const ll &val = {}, const ll &pre = {}, const ll &suf = {}, const ll &max_val = {})
		: val{val}, pre{pre}, suf{suf}, max_val{max_val} {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.val + b.val,
			std::max(a.pre, a.val + b.pre),
			std::max(a.suf + b.val, b.suf),
			std::max({a.max_val, b.max_val, a.suf + b.pre})
		};
	}
};
struct Node {
	Info val;
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

template <typename T>
void build(int l, int r, int id, const T &a) {
	if (l == r) {
		seg[id].val = {a[l], a[l], a[l], a[l]};
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2, a);
		build(mid + 1, r, id * 2 + 1, a);
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int main() {

}