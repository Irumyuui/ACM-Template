#include <bits/stdc++.h>
using namespace std;

constexpr uint64_t P = 31, M = (1e9 + 7);

constexpr int N = 1e6 + 10;

uint64_t p[N], hs[N];
char str[N];

void init() {
	p[0] = 1;
	for (uint64_t i = 1; i < N; i ++) {
		p[i] = p[i - 1] * P % M;
	}
}


void get_str_hash(int n) {
	hs[0] = 0;
	for (int i = 1; i <= n; i ++) {
		hs[i] = (hs[i - 1] * P % M + str[i]) % M;
	}
}

uint64_t substr_hash(int l, int r) {
	return ((hs[r] - hs[l] * p[r - l + 1] % M) + M % M);
}

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;

	for (int i = 1; i <= n; i ++) {
		str[i] = s[i - 1];
	}

	init();
	get_str_hash(n);

}