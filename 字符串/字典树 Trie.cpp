#include <bits/stdc++.h>
using namespace std;

template <int N, int M>
struct Trie {
	int nex[N][M];
	int cnt[N];
	int tt = 0;
	void insert(const string &s) {
		int p{};
		for (auto i : s) {
			int nx = i - 'a';
			if (nex[p][nx] == 0) {
				nex[p][nx] = ++ tt;
			}
			p = nex[p][nx];
		}
		cnt[p] ++;
	}
};

int main() {
	
}

namespace _Trie {
	struct Trie {
		std::vector<std::array<int,11>> next;
		void reserve(int _n) {
			next.reserve(_n);
		}
		void assign() {
			next.assign(1, {});
		}
		void insert(const std::vector<int> &v) {
			int p = 0;
			for (auto nx : v) {
				if (next[p][nx] == 0) {
					next[p][nx] = next.size();
					next.push_back({});
				}
				p = next[p][nx];
			}
		}
	};
}