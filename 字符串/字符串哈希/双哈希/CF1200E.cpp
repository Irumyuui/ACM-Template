#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

const int N = 1e6 + 10;

constexpr uint64_t P[2] = {131, 133}, M[2] = {19260817, ll(1e9 + 9)};
array<uint64_t,2> p[N], hs[N];
char str[N];

auto Solve() -> void {
	p[0] = {1, 1};
	for (int i = 1; i < N; i ++) {
		p[i] = {
			p[i - 1][0] * P[0] % M[0],
			p[i - 1][1] * P[1] % M[1]
		};
	}

	auto get_substr_hs = [&](int l, int r) -> array<uint64_t,2> {
		return {
			(hs[r][0] - hs[l - 1][0] * p[r - l + 1][0] % M[0] + M[0]) % M[0],
			(hs[r][1] - hs[l - 1][1] * p[r - l + 1][1] % M[1] + M[1]) % M[1],
		};
	};

	int n;
	cin >> n;
	
	int nn = 0;
	for (int _ = 1; _ <= n; _ ++) {
		string s;
		cin >> s;

		int p = 0;
		array<uint64_t,2> shs{};
		for (int j = 1; j <= min<int>(nn, s.size()); j ++) {
			auto x = s[j - 1];
			shs = {
				(shs[0] * P[0] + x) % M[0],
				(shs[1] * P[1] + x) % M[1],
			};

			int l = nn - j + 1, r = nn;
			if (get_substr_hs(l, r) == shs) {
				p = j;
			}
		}

		for (int i = p; i < s.size(); i ++) {
			++ nn;
			auto x = str[nn] = s[i];
			hs[nn] = {
				(hs[nn - 1][0] * P[0] + x) % M[0],
				(hs[nn - 1][1] * P[1] + x) % M[1],
			};
		}
	}

	for (int i = 1; i <= nn; i ++) {
		cout << str[i];
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	for (int test = 1; test <= tot_test; test += 1) {
		Solve();
	}
}