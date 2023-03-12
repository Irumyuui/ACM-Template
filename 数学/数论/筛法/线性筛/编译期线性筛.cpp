#include <bits/stdc++.h>

template <int32_t N>
struct Prime {
	std::array<int32_t,N> prime;
	std::array<bool,N> no_pri;
	int32_t n;
	constexpr Prime() : prime{}, no_pri{}, n{0} {
		no_pri[0] = 1;
		no_pri[1] = 1;
		for (int32_t i = 2; i < N; i ++) {
			if (!no_pri[i]) {
				prime[n ++] = i;
			}
			for (int32_t j = 0; j < n; j ++) {
				int64_t tag = int64_t{i} * prime[j];
				if (tag >= N) break;
				no_pri[tag] = true;
				if (i % prime[j] == 0) break;
			}
		}
	}
};
constexpr Prime<100000> pri;  // limit is 1e5