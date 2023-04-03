#include <vector>
#include <algorithm>

struct Graph {
	struct Edge {
		int to, next;
		Edge(int to = {}, int next = -1)
			: to{to}, next{next} {}
	};
	
	std::vector<Edge> edge;
	std::vector<int> head;
	int n;

	Graph(int _n) : head(_n, -1), n(_n) {
		edge.reserve(int(1e6));
	}

	void add_edge(int from, int to) {
		edge.emplace_back(to, head[from]); head[from] = int(head.size()) - 1;
	}
};