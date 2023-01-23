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