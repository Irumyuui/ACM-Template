#include <bits/stdc++.h>
using namespace std;

constexpr uint64_t P = 131;
constexpr int N = 1e5 + 10;

uint64_t p[N], hs[N];
char str[N];

void init(int n) {
	p[0] = 1; hs[0] = 0;
	for (int i = 1; i <= n; i ++) {
		p[i] = p[i - 1] * P;
		hs[i] = hs[i - 1] * P + str[i];
	}
}

uint64_t substr_hash(int l, int r) {
	return hs[r] - hs[l - 1] * p[r - l + 1];
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	string s;
	cin >> s;

	for (int i = 1; i <= n; i ++) {
		str[i] = s[i - 1];
	}
	init(n);

	cout << substr_hash(1, 2) << ' ' << substr_hash(3, 4) << '\n';
}