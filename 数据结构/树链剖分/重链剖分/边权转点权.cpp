#include <bits/stdc++.h>

const int N = 1e5 + 10, M = 1e6 + 10;

struct Edge {
	int to, id, next;
} edge[M];
int head[N], eid_to_v[N], tt = -1;
void init() {
	std::fill(std::begin(head), std::end(head), -1);
	tt = -1;
}
void add_edge(int from, int to, int eid) {
	edge[++ tt] = {to, eid, head[from]}; head[from] = tt;
	edge[++ tt] = {from, eid, head[to]}; head[to] = tt;
}

int dep[N], top[N], fa[N], siz[N], son[N], dfn[N], rnk[N], stamp = 0;

void build(int root) {
	auto dfs1 = [&](auto &&dfs, int from, int eid) -> void {
		eid_to_v[from] = eid;
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to, neid = edge[ed].id;
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				fa[to] = fa[from] + 1;
				dfs(dfs, to, neid);
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
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to;
			if (to != fa[from] && to != son[from])
				dfs(dfs,to,to);
		}
	};
	std::fill(std::begin(dep),std::end(dep),-1);
	dep[root] = stamp = 0;
	dfs1(dfs1,root,0);
	dfs2(dfs2,root,root);
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

int n;

// lca 不加
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
	if (dep[a] < dep[b])
		ret = ret + query(1, n, 1, dfn[a] + 1, dfn[b]);
	return ret.val;
}