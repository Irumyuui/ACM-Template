#include <bits/stdc++.h>

using ll = int64_t;

const int N = 1e5 + 10;

struct Info {
	ll val, bef_val;
	bool ok;
	Info(ll v = {}, bool ok = false) : val(v), bef_val(-(1 << 30)) {} 
	void init(ll v) {
		bef_val = val;
		val = v;
	}
	void update() {
		ok = val == bef_val;
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.val + b.val,
			a.ok && b.ok
		};
	}
};
struct Node {
	Info val;
} seg[N << 2];


void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

bool have = false;
void modify(int l, int r, int id, int ml, int mr) {
	if (seg[id].val.ok) 
		return;
	if (l == ml && r == mr) {
		if (l == r) {
			// do..
			seg[id].val.update();
			if (seg[id].val.ok == false) {
				have = true;
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

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr)	{
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) 
			return query(l, mid, id * 2, ql, qr);
		else if (ql > mid)
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		else
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
	}
}