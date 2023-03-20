#include <bits/stdc++.h>
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using namespace std;
using ll = int64_t;

const int N = 2e5 + 10;

struct Edge {
	int to, eid, w;
	Edge(int to = {}, int eid = {}, int w = {}) : to{to}, eid{eid}, w{w} {}	
};
vector<Edge> adj[N];

void add_edge(int from, int to, int eid, int w) {
	adj[from].emplace_back(to, eid, w);
	adj[to].emplace_back(from, eid, w);
}

int dep[N], son[N], siz[N], fa[N], top[N], dfn[N], rnk[N];
// evid := edge id to v
// veid := v id to edge
int evid[N], veid[N], vw[N];
int stamp = 0;

void build(int root) {
	auto dfs1 = [&](auto &&dfs, int from, int eid, int ew) -> void {
		evid[eid] = from;
		veid[from] = eid;
		vw[from] = ew;
		siz[from] = 1;
		son[from] = -1;
		for (auto [to, eid, ew] : adj[from]) {
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				fa[to] = from;
				dfs(dfs, to, eid, ew);
				siz[from] += siz[to];
				if (son[from] == -1 || siz[to] > siz[son[from]]) {
					son[from] = to;
				}
			}
		}
	};
	auto dfs2 = [&](auto &&dfs, int from, int root) -> void {
		top[from] = root;
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		if (son[from] == -1) {
			return;
		}
		dfs(dfs, son[from], root);
		for (auto [to, _, __] : adj[from]) {
			if (to != son[from] && to != fa[from]) {
				dfs(dfs, to, to);
			}
		}
	};
	std::fill(std::begin(dep), std::end(dep), -1);
	dep[root] = stamp = 0;
	dfs1(dfs1, root, 0, 0);
	dfs2(dfs2, root, root);
}

template <typename T>
struct Info {
	T val;
	Info(const T &val = {}) : val{val} {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info{
			a.val + b.val
		};
	}
};
struct Node {
	Info<ll> val;
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = vw[rnk[l]];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, ll d) {
	if (l == r) {
		seg[id].val = d;
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

Info<ll> query(int l, int r, int id, int ql, int qr) {
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

void Main() {
	int n;
	cin >> n;

	auto Query = [&](int a, int b) {
		Info<ll> ret;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			ret = ret + query(1, n, 1, dfn[top[a]], dfn[a]);
			a = fa[top[a]];
		}
		if (dfn[a] > dfn[b]) {
			swap(a, b);
		}
		if (dfn[a] < dfn[b]) {
			ret = ret + query(1, n, 1, dfn[a] + 1, dfn[b]);
		}
		return ret;
	};
}

int main() {

}