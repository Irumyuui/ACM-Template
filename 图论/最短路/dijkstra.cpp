#include <bits/stdc++.h>
using namespace std;
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 1e5 + 10;
vector<pair<int,int>> edge[N];
void add_edge(int from, int to, int w) {
	edge[from].push_back({to, w});
}

int dis[N];
bool vis[N];

void dijkstra(int sta) {
	fill(begin(dis), end(dis), inf<int>);
	fill(begin(vis), end(vis), false);
	dis[sta] = 0;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
	q.push({dis[sta], sta});
	while (!q.empty()) {
		int from = q.top().second;
		q.pop();
		if (vis[from]) continue;
		vis[from] = true;
		for (auto [to, w] : edge[from]) {
			if (!vis[to] && dis[to] > dis[from] + w) {
				dis[to] = dis[from] + w;
				q.push({dis[to], to});
			}
		}
	}
}