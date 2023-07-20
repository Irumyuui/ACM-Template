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

namespace RoyalGuard::Graph {
	template <typename EdgeInfo>
	class AdjacencyList {
	public:
		AdjacencyList() = default;
		AdjacencyList(int n) : adj(n) {}

		auto Count() const {
			return adj.size();
		}

		auto Count(int v) const {
			return adj[v].size();
		}

		void Assign(int n) {
			adj.assign(n, std::vector<EdgeInfo>{});
		}

		void Clear() {
			adj.clear();
		}

		void Clear(int v) {
			adj[v].clear();
		}

		void AddDirectedEdge(int from, int to, EdgeInfo &&info) {
			adj[from].emplace_back(to, info);
		}
		
		template <typename... Args>
		void AddDirectedEdge(int from, int to, Args&& ...args) {
			adj[from].emplace_back(to, args...);
		}
		
		void AddUndirectedEdge(int from, int to, EdgeInfo &&info) {
			AddDirectedEdge(from, to, info);
			AddDirectedEdge(to, from, info);
		}

		template <typename... Args>
		void AddUndirectedEdge(int from, int to, Args&& ...args) {
			AddDirectedEdge(from, to, args...);
			AddDirectedEdge(to, from, args...);
		}

		auto& operator [] (int idx) {
			return adj[idx];
		}

		const auto& operator [] (int idx) const {
			return adj[idx];
		}

	private:
		std::vector<std::vector<EdgeInfo>> adj;		
	};

	template <>
	class AdjacencyList<void> {
	public:
		AdjacencyList() = default;
		AdjacencyList(int n) : adj(n) {}

		auto Count() const {
			return adj.size();
		}

		auto Count(int v) const {
			return adj[v].size();
		}

		void Assign(int n) {
			adj.assign(n, std::vector<int>{});
		}

		void Clear() {
			adj.clear();
		}

		void Clear(int v) {
			adj[v].clear();
		}

		void AddDirectedEdge(int from, int to) {
			adj[from].emplace_back(to);
		}

		void AddUndirectedEdge(int from, int to) {
			AddDirectedEdge(from, to);
			AddDirectedEdge(to, from);
		}

		auto& operator [] (int idx) {
			return adj[idx];
		}

		const auto& operator [] (int idx) const {
			return adj[idx];
		}

	private:
		std::vector<std::vector<int>> adj;
	};
}