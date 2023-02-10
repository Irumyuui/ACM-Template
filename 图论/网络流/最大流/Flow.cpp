#include <bits/stdc++.h>

const int N = (1 << 17) + 2, M = 2e6 + 10;
struct Edge {
	int to, cap, next;
} edge[M];
int head[N], cur[N], tt = -1, lv[N];

void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}
void add_edge(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
}

bool bfs(int s, int t) {
	memset(lv, -1, sizeof lv);
	std::copy(std::begin(head), std::end(head), cur);
	lv[s] = 0;
	std::queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to, cap = edge[ed].cap;
			if (cap > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[t] != -1;
}
int dfs(int from, int t, int flow) {
	if (from == t) return flow;
	int lesf = flow;
	for (int &ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, t, std::min(cap, lesf));
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	return flow - lesf;
}
int flow(int s, int t) {
	int ret = 0;
	while (bfs(s, t)) {
		ret += dfs(s, t, std::numeric_limits<int>::max());
	}
	return ret;
}