/**
 * https://codeforces.com/contest/915/problem/E
*/

#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

struct Info {
	int val;
	Info(int val = {}) : val{val} {}
	Info operator + (const Info &a) const {
		return Info {
			val + a.val
		};
	}
};
struct Node {
	Info val;
	char lz;
	int lc, rc;
	Node(const Info &val = {}, char lz = -1, int lc = {}, int rc = {}) : val{val}, lz{lz}, lc{lc}, rc{rc} {}
};
vector<Node> seg(1);

int get_node() {
	seg.push_back(Node());
	return int(seg.size()) - 1;
}

void rise(int id) {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

void update(int l, int r, int &id, int d) {
	if (id == 0) id = get_node();
	seg[id].val = (r - l + 1) * d;
	seg[id].lz = d;
}

void down(int l, int r, int id) {
	if (seg[id].lz == -1)
		return;
	int mid = l + ((r - l) >> 1);
	update(l, mid, seg[id].lc, seg[id].lz);
	update(mid + 1, r, seg[id].rc, seg[id].lz);
	seg[id].lz = -1;
}

void modify(int l, int r, int &id, int ml, int mr, int d) {
	if (id == 0)
		id = get_node();
	if (l == ml && r == mr) {
		update(l, r, id, d);
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, seg[id].lc, ml, mr, d);
		} else if (ml > mid) {
			modify(mid + 1, r, seg[id].rc, ml, mr, d);
		} else {
			modify(l, mid, seg[id].lc, ml, mid, d);
			modify(mid + 1, r, seg[id].rc, mid + 1, mr, d);
		}
		rise(id);
	}
}

void Main() {
	seg.reserve(int(15001000));
	
	int n;
	cin >> n;

	int q, root = 0;
	modify(1, n, root, 1, n, 1);
	cin >> q;
	for (int t = 1; t <= q; t ++) {
		int l, r, opt;
		cin >> l >> r >> opt;
		if (opt == 1) {
			modify(1, n, root, l, r, 0);
		} else {
			modify(1, n, root, l, r, 1);
		}
		cout << seg[root].val.val << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}