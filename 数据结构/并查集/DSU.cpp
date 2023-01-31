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

namespace _DSU {
	struct DSU {
		int n, cnt;
		std::vector<int> dad;
		explicit DSU(int _n = {}) : dad(_n, -1), n(_n), cnt(_n) {}
		auto assign(int _n) -> void {
			n = cnt = _n;
			dad.assign(_n, -1);
		}
		auto find(int id) -> int {
			if (dad[id] <= -1)
				return dad[id];
			return dad[id] = find(dad[id]);
		}
		auto merge(int a, int b) -> bool {
			a = find(a); b = find(b);
			if (a == b) return false;
			dad[a] += dad[b];
			dad[b] = a;
			cnt --;
			return true;	
		}
		auto is_same(int a, int b) -> bool {
			return find(a) == find(b);
		}
		auto set_size(int id) -> int {
			return -dad[find(id)];
		}
		auto set_count() const -> int {
			return cnt;
		}
	};
}

int main() {
	int n;
	std::vector<int> dad(n + 1, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] > -1) return dad[x] = Find(Find, x);
		return x;
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a), b = Find(Find, b);
		if (a == b) return false;
		dad[a] += dad[b];
		dad[b] = a;
		return true;
	};
	auto Is_Same = [&](int a, int b) {
		return Find(Find, a) == Find(Find, b);
	};
}