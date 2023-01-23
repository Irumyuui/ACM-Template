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

template <typename T = int64_t, typename Opt = T(*)(T,T)>
struct BinaryIndexedTree {
	std::vector<T> bit;
	int32_t n;
	const Opt &opt;
	explicit BinaryIndexedTree(int32_t _n, const T &val, const Opt &_opt) : bit(_n + 1, val), n(_n), opt(_opt) {}
	void update(int32_t x, const T &d) {
		assert(x > 0);
		for (int32_t i = x; i <= n; i += i & -i) {
			bit[i] = opt(bit[i], d);
		}
	}
	auto ask(int32_t x, T &&ret = {}) {
		for (int32_t i = x; i > 0; i -= i & -i) {
			ret = opt(ret, bit[i]);
		}
		return ret;
	}
};