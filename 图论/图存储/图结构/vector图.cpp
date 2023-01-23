#include <bits/stdc++.h>

struct Graph {
	std::vector<std::vector<int>> g;
	int n;
	Graph(const int _n) : g(_n), n(n) {}
	constexpr void add_edge(int from, int to) {
		g[from].emplace_back(to);
	}
	constexpr void add_edges(int from, int to) {
		add_edge(from, to); add_edge(to, from);
	}
};