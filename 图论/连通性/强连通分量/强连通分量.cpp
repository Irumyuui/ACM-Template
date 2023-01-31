#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> edge[N];

void add_edge(int from, int to) {
	edge[from].push_back(to);
}

int dfn[N], low[N], stamp = 0;
stack<int> st;
bool inst[N];

vector<int> scc[N];
int scc_cnt = 0, scc_id[N];

void dfs(int from) {
	dfn[from] = low[from] = ++ stamp;
	inst[from] = true;
	st.push(from);
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			dfs(to);
			low[from] = min(low[from], low[to]);
		} else if (inst[to]) {
			low[from] = min(low[from], dfn[to]);
		}
	}
	if (dfn[from] == low[from]) {
		++ scc_cnt;
		int now = 0;
		do {
			now = st.top();
			st.pop();
			inst[now] = false;
			scc_id[now] = scc_cnt;
			scc[scc_cnt].push_back(now);
		} while (now != from);
	}
}

int main() {

}