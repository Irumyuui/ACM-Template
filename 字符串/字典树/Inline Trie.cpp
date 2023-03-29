#include <bits/stdc++.h>

void Main() {
	
	std::vector<std::array<int,26>> trie{{}};
	trie.reserve(int(1e6 + 10));
	auto Insert = [&](const std::string &&s) {
		int p = 0;
		for (int x : s) {
			int nx = x - 'a';
			if (trie[p][nx] == 0) {
				trie[p][nx] = trie.size();
				trie.push_back({});
			}
			p = trie[p][nx];
		}
	};

}

int main() {
	
}