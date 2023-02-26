#include <bits/stdc++.h>

struct Bit_Trie {
	std::vector<std::array<int,2>> trie;

	Bit_Trie(int __init_size__ = int(1e6 + 10)) : trie(1, std::array<int,2>{}) {
		trie.reserve(__init_size__);
	}

	auto get_node() -> int {
		int p = trie.size();
		trie.push_back({});
		return p;
	}
	
	auto insert(int x) -> void {
		int p = 0;
		for (int i = 30; i >= 0; i --) {
			int d = (x >> i) & 1;
			if (trie[p][d] == 0) {
				trie[p][d] = get_node();
			}
			p = trie[p][d];
		}
	}
};