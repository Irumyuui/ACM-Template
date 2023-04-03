#include <vector>
#include <algorithm>

struct Graph {
	std::vector<std::vector<int>> adj;
	int n;	

	Graph(int _n = {}) : adj(_n), n{_n} {}
	
	void add_edge(int from, int to) {
		adj[from].emplace_back(to);
	}

	void unique() {
		for (auto &vec : adj) {
			std::sort(vec.begin(), vec.end());
			vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
		}
	}

	std::vector<int>& operator [] (const int idx) {
		return adj[id];
	}
	const std::vector<int>& operator [] (const int idx) const {
		return adj[id];
	}
};