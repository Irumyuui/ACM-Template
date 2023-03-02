#include <bits/stdc++.h>

const int N = 2e5 + 10;

// 并查集
int dad[N];
int find(int x) {
	if (dad[x] <= -1) {
		return x;
	}
	return dad[x] = find(dad[x]);
}

// 图 adj
std::vector<int> edge[N];
int dfn[N], rnk[N], siz[N], stamp = 0, vw[N];
void add_edge(int from, int to) {
	edge[from].emplace_back(to);
	edge[to].emplace_back(from);
}

int fa[N][31];
int lg[N];

// 初始化 log_2
void init() {
	lg[0] = lg[1] = 0;
	for (int i = 2; i < N; i ++) {
		lg[i] = lg[i / 2] + 1;
	}
}

// 为树赋予 dfs 序列以维护
void dfs(int now, int dad) {
	dfn[now] = ++ stamp;
	rnk[stamp] = now;
	siz[now] = 1;

	// 用树上倍增的方式
	for (int i = 1; i <= 30; i ++) {
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	}

	for (auto nex : edge[now]) {
		if (nex != dad) {
			dfs(nex, now);
			siz[now] += siz[nex];
		}
	}
}

// 可持久化线段树
struct Node {
	int val;
	int lc, rc;
	Node() : val(0), lc(0), rc(0) {}
} seg[N << 4];
int ver[N], tt = 0;
int getNode() {
	return ++ tt;
}
void rise(int id) {
	seg[id].val = seg[ seg[id].lc ].val + seg[ seg[id].rc ].val;
}
void extend(int oid, int nid) {
	seg[nid].lc = seg[oid].lc; seg[nid].rc = seg[oid].rc;
}
void build(int l, int r, int &id) {
	id = getNode();
	if (l == r) {
		seg[id].val = -1;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, seg[id].lc);
		build(mid + 1, r, seg[id].rc);
		rise(id);
	}
}
void insert(int l, int r, int oid, int &nid, int tag, int d) {
	nid = getNode();
	if (l == r) {
		seg[nid].val = seg[oid].val + d;
	} else {
		int mid = l + ((r - l) >> 1);
		extend(oid, nid);
		if (tag <= mid) {
			insert(l, mid, seg[oid].lc, seg[nid].lc, tag, d);
		} else {
			insert(mid + 1, r, seg[oid].rc, seg[nid].rc, tag, d);
		}
		rise(nid);
	}
}
int query_mx_kth(int l, int r, int lid, int rid, int kth) {
	if (seg[rid].val - seg[lid].val < kth) {
		return -1;
	} else if (l == r) {
		return l;
	} else {
		int mid = l + ((r - l) >> 1);
		int x = seg[ seg[rid].rc ].val - seg[ seg[lid].rc ].val;
		if (x >= kth) {
			return query_mx_kth(mid + 1, r, seg[lid].rc, seg[rid].rc, kth);
		} else {
			return query_mx_kth(l, mid, seg[lid].lc, seg[rid].lc, kth - x);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<int> hei(n + 1), chei(n);
	for (int i = 1; i <= n; i ++) {
		std::cin >> hei[i];
		chei[i - 1] = hei[i]; 
	}
	// 离散化
	std::ranges::sort(chei);
	chei.erase(std::unique(chei.begin(), chei.end()), chei.end());
	for (int i = 1; i <= n; i ++) {
		hei[i] = std::ranges::lower_bound(chei, hei[i]) - chei.begin() + 1;
	}
	
	// 读取边
	std::vector<std::array<int,3>> eds(m);
	for (auto &[a, b, w] : eds) {
		std::cin >> a >> b >> w;
	}
	std::ranges::sort(eds, [](const auto &a, const auto &b) -> bool {
		return a[2] < b[2];
	});
	memset(dad, -1, sizeof(dad));
	memset(vw, -1, sizeof(vw));
	
	// 构建 Kruskal 重构树
	int tot = n;
	for (auto [a, b, w] : eds) {
		a = find(a); b = find(b);
		if (a != b) {
			tot ++;
			dad[a] = dad[b] = tot;
			vw[tot] = w;
			fa[a][0] = fa[b][0] = tot;
			add_edge(tot, a);
			add_edge(tot, b);
		}
	}

	init();
	for (int i = tot; i >= 1; i --) {
		if (!dfn[i]) {
			dfs(i, 0);
		}
	}

	// 建主席树
	int nn = chei.size();
	build(1, nn, ver[0]);
	for (int i = 1; i <= tot; i ++) {
		if (vw[rnk[i]] == -1) {
			insert(1, nn, ver[i - 1], ver[i], hei[rnk[i]], 1);
		} else {
			ver[i] = ver[i - 1];
		}
	}

	// 处理询问
	while (q --) {
		int v, x, k;
		std::cin >> v >> x >> k;
		if (v < 1 || v > n || k > n) {
			std::cout << -1 << '\n';
		} else {
			// 向上跳合适的节点
			for (int i = 30; i >= 0; i --) {
				if (fa[v][i] && vw[fa[v][i]] <= x) {
					v = fa[v][i];
				}
			}

			// 可持久化权值线段树查询第 k 大值
			int ret = query_mx_kth(1, nn, ver[dfn[v] - 1], ver[dfn[v] + siz[v] - 1], k);
			if (ret == -1) {
				std::cout << -1 << '\n';
			} else {
				std::cout << chei[ret - 1] << '\n';
			}
		}
	}
}