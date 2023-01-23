#include <bits/stdc++.h>

using namespace std;

// template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

// const int N = 114514, M = 1919810;
// struct Edge {
// 	int to, cap, next;
// 	Edge(int to = {}, int cap = {}, int next = -1) : to(to), cap(cap), next(next) {}
// } edge[M];
// int head[N], cur[N], lv[N], tt = -1;
// void init() {
// 	tt = -1;
// 	memset(head, -1, sizeof head);
// }
// void add_edge(int from, int to, int cap) {
// 	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
// 	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
// }
// int maxflow(int s, int t) {
// 	auto bfs = [&] {
// 		std::copy(std::begin(head), std::end(head), std::begin(cur));
// 		memset(lv, -1, sizeof lv);
// 		std::queue<int> q;
// 		q.emplace(s);
// 		lv[s] = 0;
// 		while (!q.empty()) {
// 			int from = q.front();
// 			q.pop();
// 			for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
// 				if (edge[ed].cap > 0 && lv[edge[ed].to] == -1) {
// 					lv[edge[ed].to] = lv[from] + 1;
// 					q.emplace(edge[ed].to);
// 				}
// 			}
// 		}
// 		return lv[t] != -1;
// 	};
// 	auto dfs = [&](auto &&dfs, int from, int flow) -> int {
// 		if (from == t) return flow;
// 		int lesf = flow;
// 		for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
// 			if (edge[ed].cap > 0 && lv[edge[ed].to] == lv[from] + 1) {
// 				auto ret = dfs(dfs, edge[ed].to, std::min(lesf, edge[ed].cap));
// 				lesf -= ret;
// 				edge[ed].cap -= ret;
// 				edge[ed ^ 1].cap += ret;
// 			}
// 		}
// 		return flow - lesf;
// 	};
// 	int flow = 0;
// 	while (bfs()) flow += dfs(dfs, s, inf<int>);
// 	return flow;
// }

template <typename Type = int32_t>
struct Dinic_maxflow {
	static constexpr Type __INF = std::numeric_limits<Type>::max() / 2;
	struct Edge {
		int to, next;
		Type cap;
		Edge(int to = {}, Type cap = {}, int next = -1) : to(to), cap(cap), next(next) {}
	};
	std::vector<Edge> edge;
	std::vector<int> head, cur, lv;
	int tt;
	Dinic_maxflow(int _n = {}, int _m = {}) {
		init(_n, _m);
	}
	void init(int n, int m) {
		tt = -1;
		head.assign(n, -1);
		cur.resize(n);
		lv.resize(n);
		edge.assign(m, Edge{});
	}
	void add_edge(int from, int to, Type cap) {
		edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	}
	auto maxflow(int s, int t) {
		auto bfs = [&] {
			std::copy(std::begin(head), std::end(head), std::begin(cur));
			std::fill(std::begin(lv), std::end(lv), -1);
			std::queue<int> q;
			q.emplace(s);
			lv[s] = 0;
			while (!q.empty()) {
				int from = q.front();
				q.pop();
				for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
					if (edge[ed].cap > 0 && lv[edge[ed].to] == -1) {
						lv[edge[ed].to] = lv[from] + 1;
						q.emplace(edge[ed].to);
					}
				}
			}
			return lv[t] != -1;
		};
		auto dfs = [&](auto &&dfs, int from, Type flow) -> Type {
			if (from == t) return flow;
			auto lesf = flow;
			for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
				cur[from] = ed;
				if (edge[ed].cap > 0 && lv[edge[ed].to] == lv[from] + 1) {
					auto ret = dfs(dfs, edge[ed].to, std::min<Type>(lesf, edge[ed].cap));
					lesf -= ret;
					edge[ed].cap -= ret;
					edge[ed ^ 1].cap += ret;
				}
			}
			return flow - lesf;
		};
		Type flow = 0;
		while (bfs()) flow += dfs(dfs, s, __INF);
		return flow;
	}
	auto& operator [] (int idx) { return edge[idx]; }
	const auto& operator [] (int idx) const { return edge[idx]; }
};

template <typename Capacity>
struct MaxFlow_Dinic {
	using Capacity_Type = Capacity;
	static constexpr Capacity __INF = std::numeric_limits<Capacity>::max() / 2;
	struct Edge {
		int to, next;
		Capacity cap;
		Edge(const int &_to = {}, const Capacity &_cap = {}, const int &_next = {-1}) : to(_to), next(_next), cap(_cap) {}
	};
	std::vector<Edge> edge;
	std::vector<int> head, cur, lv;
	int last_edge_pos;
	int S, T;  // Source and Sink
	MaxFlow_Dinic(int _n = {}, int _m = {}, int _S = {}, int _T = {}) : S(_S), T(_T) {
		assign(_n, _m);
	}
	void assign(int _n, int _m) {
		last_edge_pos = -1;
		head.assign(_n, -1);
		cur.resize(_n);
		lv.resize(_n);
		edge.clear();
		edge.reserve(_m);
	}
	void add_edge(int from, int to, const Capacity &cap) {
		edge.emplace_back(to, cap, head[from]); head[from] = ++ last_edge_pos; 
	}
	void add_edges(int from, int to, const Capacity &cap) {
		add_edge(from, to, cap);
		add_edge(to, from, Capacity{0});
	}
	auto maxflow(int s, int t) {
		auto bfs = [&] {
			std::copy(std::begin(head), std::end(head), std::begin(cur));
			std::fill(std::begin(lv), std::end(lv), -1);
			std::queue<int> q;
			q.emplace(s);
			lv[s] = 0;
			while (!q.empty()) {
				int from = q.front();
				q.pop();
				for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
					if (edge[ed].cap > 0 && lv[edge[ed].to] == -1) {
						lv[edge[ed].to] = lv[from] + 1;
						q.emplace(edge[ed].to);
					}
				}
			}
			return lv[t] != -1;
		};
		auto dfs = [&](auto &&dfs, int from, Capacity flow) -> Capacity {
			if (from == t) return flow;
			auto lesf = flow;
			for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
				cur[from] = ed;
				if (edge[ed].cap > 0 && lv[edge[ed].to] == lv[from] + 1) {
					auto ret = dfs(dfs, edge[ed].to, std::min<Capacity>(lesf, edge[ed].cap));
					lesf -= ret;
					edge[ed].cap -= ret;
					edge[ed ^ 1].cap += ret;
				}
			}
			return flow - lesf;
		};
		Capacity flow = 0;
		while (bfs()) flow += dfs(dfs, s, __INF);
		return flow;
	}
	auto maxflow() { return maxflow(S, T); }
	auto& operator [] (int idx) { return edge[idx]; }
	const auto& operator [] (int idx) const { return edge[idx]; }
	auto& begin() { return edge.begin(); }
	const auto& cbegin() const { return edge.cbegin(); }
	auto& end() { return edge.end(); }
	const auto& cend() const { return edge.cend(); }
	auto& rbegin() { return edge.rbegin(); }
	const auto& crbegin() const { return edge.crbegin(); }
	auto& rend() { return edge.rend(); }
	const auto& crend() const { return edge.crend(); }
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	
	// Dinic_maxflow<int> dinic(n + 1, m * 2);
	MaxFlow_Dinic<int> dinic(n + 1, m * 2, s, t);
	// dinic.init(n + 1, m * 2);
	for (int i = 0; i < m; i ++) {
		int u, v, c;
		cin >> u >> v >> c;
		dinic.add_edges(u, v, c);
		// dinic.add_edge(u, v, c);
		// dinic.add_edge(v, u, 0);
	}

	cout << dinic.maxflow() << '\n';
	// cout << dinic.maxflow(s, t) << '\n';
}