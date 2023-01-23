#include <bits/stdc++.h>

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
const int N = 1e5 + 10, M = 2e6 + 10;

struct Edge {
	int to, cap, cost, next;
	Edge(int to = {}, int cap = {}, int cost = {}, int next = -1) : to(to), cap(cap), cost(cost), next(next) {}
} edge[M];
int head[N], cur[N], tt = -1;
int dis[N];
bool vis[N];
void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}
void add_edge(int from, int to, int cap, int cost) {
	edge[++ tt] = {to, cap, cost, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, -cost, head[to]}; head[to] = tt;
}

std::pair<int,int> dinic(int S, int T) {
	auto spfa = [&]() {
		std::fill(std::begin(dis), std::end(dis), inf<int>);
		std::copy(std::begin(head), std::end(head), cur);
		dis[S] = 0;
		std::queue<int> q;
		q.emplace(S);
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			vis[from] = false;
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				int to = edge[ed].to, cap = edge[ed].cap, cost = edge[ed].cost;
				if (cap > 0 && dis[to] > dis[from] + cost) {
					dis[to] = dis[from] + cost;
					if (!vis[to]) {
						vis[to] = true;
						q.emplace(to);
					}
				}
			}
		}
		return dis[T] != inf<int>;
	};
	auto dfs = [&](auto &&dfs, int from, int flow) -> int {
		if (from == T) return flow;
		int lesf = flow;
		vis[from] = true;
		for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			int to = edge[ed].to, cap = edge[ed].cap, cost = edge[ed].cost;
			if (!vis[to] && cap > 0 && dis[to] == dis[from] + cost) {
				auto ret = dfs(dfs, to, std::min(cap, lesf));
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
		vis[from] = false;
		return flow - lesf;
	};
	
	int flow = 0, cost = 0;
	while (spfa()) {
		auto ret = dfs(dfs, S, inf<int>);
		flow += ret;
		cost += ret * dis[T];
	}
	return {flow, cost};
}