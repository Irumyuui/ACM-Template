#include <bits/stdc++.h>
using namespace std;

auto Main() -> void {
	int n;
	cin >> n;
	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<int> col(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> col[i];
	}
	
	vector<int> dfn(n + 1, -1), rnk(n + 1, -1), siz(n + 1), son(n + 1);
	int stamp = 0;
	auto dfs1 = [&](auto &&dfs, int from) -> void {
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		siz[from] = 1;
		son[from] = -1;
		for (auto to : adj[from]) {
			if (dfn[to] == -1) {
				dfs(dfs, to);
				siz[from] += siz[to];
				if (son[from] == -1 || siz[to] > siz[son[from]]) {
					son[from] = to;
				}
			}
		}
	};
	dfs1(dfs1, 1);

	vector<int> col_cnt(ranges::max(col) + 1);
	int tot_col = 0;
	auto add = [&](int v) {
		if (col_cnt[col[v]] == 0) {
			tot_col ++;
		}
		col_cnt[col[v]] ++;
	};
	auto del = [&](int v) {
		col_cnt[col[v]] --;
		if (col_cnt[col[v]] == 0) {
			tot_col --;
		}
	};

	vector<int> ret(n + 1);
	auto dfs2 = [&](auto &&dfs, int from, int fa, bool keep) -> void {
		// 不保留的遍历轻儿子
		for (auto to : adj[from]) {
			if (to != fa && to != son[from]) {
				dfs(dfs, to, from, false);
			}
		}
		// 保留地遍历重儿子
		if (son[from] != -1) {
			dfs(dfs, son[from], from, true);
			for (auto to : adj[from]) {
				if (to != fa && to != son[from]) {
					for (int i = dfn[to]; i <= dfn[to] + siz[to] - 1; i ++) {
						add(rnk[i]);
					}
				}
			}
		}
		// 计算该点结果
		add(from);
		ret[from] = tot_col;
		// 如果该点不保留 清空所有信息（整个的，不是这个子树的）
		if (!keep) {
			for (int i = dfn[from]; i <= dfn[from] + siz[from] - 1; i ++) {
				del(rnk[i]);
			}
		}
	};
	dfs2(dfs2, 1, 0, false);

	for (int i = 1; i <= n; i ++) {
		cout << ret[i] << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}