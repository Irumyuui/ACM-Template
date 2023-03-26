#include <bits/stdc++.h>

int main() {
	int n;
	std::cin >> n;

	std::vector<int> dad(n + 1, -1);
	auto Find = [Find{[&](auto &&Find, int x) -> int {
		if (dad[x] == -1) {
			return x;
		}
		return dad[x] = Find(Find, dad[x]);
	}}](int x) -> int {
		return Find(Find, x); 
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(a); b = Find(b);
		if (a == b) {
			return false;
		} else {
			dad[b] = a;
			return true;
		}
	};
	auto Is_Same = [&](int a, int b) -> bool {
		return Find(a) == Find(b);
	};
}