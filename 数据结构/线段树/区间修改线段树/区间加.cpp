#include <bits/stdc++.h>

using ll = int64_t;

const int N = 2e5 + 10;

struct Info {
	ll val;
	Info(ll v = {}) : val{v} {}
	Info operator + (const Info &a) const {
		return Info{val + a.val};
	}
};
struct Node {
	Info val;
	ll lz;
	Node() : val(), lz() {}
} seg[N * 4];
ll a[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void update(int l, int r, int id, ll d) {
	seg[id].val.val += (r - l + 1) * d;
	seg[id].lz += d;
}
void down(int l, int r, int id) {
	if (seg[id].lz == 0) return;
	int mid = l + ((r - l) >> 1);
	update(l, mid, id * 2, seg[id].lz);	
	update(mid + 1, r, id * 2 + 1, seg[id].lz);	
	seg[id].lz = 0;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = a[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void modify(int l, int r, int id, int ml, int mr, ll d) {
	if (l == ml && r == mr) {
		update(l, r, id, d);
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, d);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, d);
		} else {
			modify(l, mid, id * 2, ml, mid, d);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, d);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}