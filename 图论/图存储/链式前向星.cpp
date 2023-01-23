#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

struct Edge {
	int to, next;
	Edge(int _to = 0, int _next = -1) : to(_to), next(_next) {}
} edge[M];

int head[N], tt = -1;

void init() {
	memset(head, -1, sizeof(head));
}

void add_edge(int from, int to) {
	edge[++ tt] = {to, head[from]}; head[from] = tt;
	edge[++ tt] = {from, head[to]}; head[to] = tt;  // 双向边
}