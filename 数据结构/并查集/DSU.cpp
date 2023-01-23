#include <bits/stdc++.h>

struct DSU {
	int32_t n, cnt;
	std::vector<int32_t> dad;
	explicit DSU(const int32_t _n) : dad(_n, -1), n(_n), cnt(_n) {}
	int32_t find(int32_t x) {
		if (dad[x] > -1) 
			return dad[x] = find(dad[x]);
		return x;
	}
	bool merge(int32_t a, int32_t b) {
		a = find(a); b = find(b);
		if (a == b)
			return false;
		dad[a] += dad[b];
		dad[b] = a;
		-- cnt;
		return true;
	}
	const auto count() const { return cnt; }
	bool is_same(int a, int b) { return find(a) == find(b); }
	auto count(int32_t x) { return dad[find(x)]; }
	auto& operator [] (int32_t x) { return dad[find(x)]; }
	auto begin() { return dad.begin(); }
	const auto begin() const { return dad.begin(); }
	auto end() { return dad.end(); }
	const auto end() const { return dad.end(); }
};