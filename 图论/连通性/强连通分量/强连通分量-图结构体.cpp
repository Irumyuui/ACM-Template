#include <bits/stdc++.h>

namespace Royal_Guard::Graph {

	struct SCC_Graph {
		std::vector<std::vector<int>> adj, scc_adj;
		std::vector<int> scc_id, scc_vcnt;
		int n, scc_cnt;
		
		explicit SCC_Graph(int _n) : adj(_n), scc_adj(), scc_id(_n, -1), scc_vcnt(), n{n}, scc_cnt{0} {}

		void add_edge(int from, int to) {
			adj[from].emplace_back(to);
		}
		
		void tarjan() {
			std::vector<int> dfn(n, -1), low(n, -1), st;
			std::vector<bool> inst(n);
			int stamp = 0;
			scc_cnt = 0;
			auto dfs = [&](auto &&dfs, int from) -> void {
				dfn[from] = low[from] = ++ stamp;
				st.emplace_back(from);
				inst[from] = true;
				for (auto to : adj[from]) {
					if (dfn[to] == -1) {
						dfs(dfs, to);
						low[from] = std::min(low[from], low[to]);
					} else if (inst[to]) {
						low[from] = std::min(low[from], dfn[to]);
					}
				}
				if (low[from] == dfn[from]) {
					int now = 0;
					do {
						now = st.back();
						st.pop_back();
						inst[now] = false;
						scc_id[now] = scc_cnt;
						scc_vcnt[scc_cnt] ++;
					} while (now != from);
					scc_cnt ++;
				}
			};
			for (int i = 0; i < n; i ++)
				if (dfn[i] == -1)
					dfs(dfs, i);
			
			scc_adj.assign(scc_cnt, {});
			for (int from = 0; from < scc_cnt; from ++)
				for (auto to : adj[from])
					if (scc_id[from] != scc_id[to])
						scc_adj[scc_id[from]].emplace_back(scc_id[to]);
			
			for (auto &vec : scc_adj) {
				std::sort(vec.begin(), vec.end());
				vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
			}
		}
	};

}