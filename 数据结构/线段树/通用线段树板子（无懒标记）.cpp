#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct Info {

	friend Info operator + (const Info &a, const Info &b) {

	}
};
struct Node {
	Info val;
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id) {
	if (l == r) {
		
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, int d) {
	if (l == r) {

	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, id * 2, tag, d);
		} else {
			change(mid + 1, r, id * 2 + 1, tag, d);
		}
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