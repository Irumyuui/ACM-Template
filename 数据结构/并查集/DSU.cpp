#include <bits/stdc++.h>

struct DSU {
	std::vector<int> dad;
	int dcnt;
	explicit DSU(int n) : dcnt{n}, dad(n, -1) {}	
	auto find(int id) -> int {
		if (dad[id] <= -1) {
			return id;
		}
		return dad[id] = find(dad[id]);
	}
	auto merge(int a, int b) -> bool {
		a = find(a); b = find(b);
		if (a == b) {
			return false;
		}
		dad[a] += dad[b];
		dad[b] = a;
		dcnt --;
		return true;
	};
	auto is_same(int a, int b) -> bool {
		return find(a) == find(b);
	}
	auto count() const -> int {
		return dcnt;
	}
	auto count(int x) const -> int {
		return -dad[x];		
	}
};

struct DSUS {
	std::vector<std::pair<int,std::set<int>>> dad;
	int dcnt;
	DSUS(int n) : dad(n, {-1, {}}), dcnt{n} {}
	auto find(int x) -> int {
		if (dad[x].first <= -1) {
			return dad[x].first;
		} else {
			return dad[x].first = find(dad[x].first);
		}
	}
	auto merge(int a, int b) -> bool {
		a = find(a); b = find(b);
		if (a == b) {
			return false;
		}
		if (dad[a].second.size() < dad[b].second.size()) {
			swap(dad[a], dad[b]);
		}
		dad[a].second.merge(dad[b].second);
		dad[a].second.emplace(b);
		dad[a].first += dad[b].first;
		dad[b] = {a, {}};
		return true;
	}
	auto is_same(int a, int b) -> bool {
		return find(a) == find(b);
	}
	auto count() const -> int {
		return dcnt;
	}
};

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