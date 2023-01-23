#include <bits/stdc++.h>
using namespace std;
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 1e5 + 10;
vector<pair<int,int>> edge[N];
int n;
void add_edge(int from, int to, int w) {
	edge[from].push_back({to, w});
}

int dis[N], cnt[N];
bool vis[N];

bool spfa(int sta) {
	fill(begin(dis), end(dis), inf<int>);
	fill(begin(vis), end(vis), false);
	fill(begin(cnt), end(cnt), 0);
	queue<int> q;
	q.push(sta);
	dis[sta] = 0;
	while (!q.empty()) {
		auto from = q.front();
		q.pop();
		vis[from] = false;
		for (auto [to, w] : edge[from]) {
			if (dis[to] > dis[from] + w) {
				dis[to] = dis[from] + w;
				cnt[to] = cnt[from] + 1;
				if (cnt[to] > n - 1) {
					return false;
				}
				if (!vis[to]) {
					vis[to] = true;
					q.push(to);
				}
			}
		}
	}
	return true;
}

int main() {

}