#include <bits/stdc++.h>

const int N = 1e5 + 10;
int bit[N];

void add(int x, int n, int d) {
	for (int i = x; i <= n; i += i & -i) {
		bit[i] += d;
	}
}

int ask(int x) {
	int ret = {};
	for (int i = x; i > 0; i -= x & -x) {
		ret += bit[i];
	}
	return ret;
}

int aks(int l, int r) {
	return ask(r) - ask(l - 1);
}

namespace Royal_Guard::Data_Structure::Basic_DS::Fenwick_Tree::Add {
	template <typename T>
	struct Fenwick_Tree {
		int n;
		std::vector<T> bit;
		Fenwick_Tree(int _n, const T &v = {}) : bit(_n + 1, v), n(_n) {}
		void add(int x, const T &d) {
			for (int i = x; i <= n; i += i & -i) {
				bit[i] += d;
			}
		}
		auto ask(int x) -> T {
			T ret = {};
			for (int i = x; i > 0; i -= i & -i) {
				ret += bit[i];
			}
			return ret;
		}
		auto ask(int l, int r) -> T {
			return ask(r) - ask(l - 1);
		}
	};
}
using Royal_Guard::Data_Structure::Basic_DS::Fenwick_Tree::Add::Fenwick_Tree;