#include <bits/stdc++.h>
using namespace std;

struct Node {
	int val;
	int lc, rc;
	Node(int val = {}, int lc = {}, int rc = {}) : val{val}, lc{lc}, rc{rc} {}
};
vector<int> version;
vector<Node> seg{{}};

int get_node() {
	seg.emplace_back(0, 0, 0);
	return int(seg.size()) - 1;
}
void extends(int now, int pre) {
	seg[now] = seg[pre];
}
void rise(int id) {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}
void update(int id, int d) {
	seg[id].val += d;
}

void build(int l, int r, int &now) {
	now = get_node();
	if (l == r) {

	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, seg[now].lc);
		build(mid + 1, r, seg[now].rc);
		rise(now);
	}
}

void change(int l, int r, int pre, int &now, int tag, int d) {
	now = get_node();
	extends(now, pre);
	if (l == r) {
		update(now, d);
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, seg[pre].lc, seg[now].lc, tag, d);
		} else {
			change(mid + 1, r, seg[pre].rc, seg[now].rc, tag, d);
		}
		rise(now);
	}
}

int query_max_kth(int l, int r, int pre, int now, int kth) {
	if (l == r) {
		return l;
	} else if (l > r) {
		return -1;
	} else {
		int mid = l + ((r - l) >> 1);
		if (seg[seg[now].rc].val - seg[seg[pre].rc].val >= kth) {
			return query_max_kth(mid + 1, r, seg[pre].rc, seg[now].rc, kth);
		} else {
			return query_max_kth(l, mid, seg[pre].lc, seg[now].lc, kth - (seg[seg[now].rc].val - seg[seg[pre].lc].val));
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
}