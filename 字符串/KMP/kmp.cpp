#include <bits/stdc++.h>

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	std::string s, t;
	std::cin >> s >> t;

	std::vector<int> nex(t.size(), -1);
	for (int i = 1, k = -1; i < t.size(); i ++) {
		while (k > -1 && t[k + 1] != t[i])
			k = nex[k];
	}
}