#include <bits/stdc++.h>

const int N = 1e5 + 10;
std::vector<int> edge[N];
int vw[N];
void add_edge(int from, int to) {
	edge[from].emplace_back(to);
	edge[to].emplace_back(from);
}
int dep[N], fa[N], top[N], son[N], siz[N], dfn[N], rnk[N], stamp = 0;

int n;

void build(int root) {
	auto dfs1 = [&](auto &&dfs, int from) -> void {
		son[from] = -1;
		siz[from] = 1;
		for (auto to : edge[from]) {
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				fa[to] = from;
				dfs(dfs, from);
				siz[from] += siz[to];
				if (son[from] == -1 || siz[to] > siz[son[from]]) 
					son[from] = to;
			}
		}	
	};
	auto dfs2 = [&](auto &&dfs, int from, int root) -> void {
		top[from] = root;
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		if (son[from] == -1)
			return;
		dfs(dfs, son[from], root);
		for (auto to : edge[from])
			if (to != fa[from] && to != son[from])
				dfs(dfs, to, to);
	};
	std::fill(std::begin(dep), std::end(dep), -1);
	dep[root] = stamp = 0;
	dfs1(dfs1,root);
	dfs2(dfs2,root,root);	
}

int Lca(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]])  // 下面的先跳
			std::swap(a, b);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b])
		std::swap(a, b);
	return a;
}

struct Info {
	int val;
	Info(int v = {}) : val(v) {}
	friend Info operator + (const Info &a, const Info &b) {
		return a.val + b.val;
	}
};
struct Node {
	Info val;	
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

// l, r 指的是 dfs 序
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = vw[rnk[l]];  // dfs序反推节点
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, int d) {
	if (l == r) {
		seg[id].val = d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid)
			change(l, mid, id * 2, tag, d);
		else
			change(mid + 1, r, id * 2 + 1, tag, d);
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
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

// 查询树上节点范围
// 类似于 lca
int query(int a, int b) {
	Info ret = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) 
			std::swap(a, b);
		ret = ret + query(1, n, 1, dfn[top[a]], dfn[a]);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b])
		std::swap(a, b);
	ret = ret + query(1, n, 1, dfn[a], dfn[b]);
	return ret.val;
}