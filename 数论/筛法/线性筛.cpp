#include <bits/stdc++.h>

// 普通线性筛
template <int N, typename T = int32_t>
struct Euler_bitset {
	std::vector<T> prime;
	std::bitset<N> no_prime;
	Euler_bitset() : no_prime{} {
		no_prime[0] = no_prime[1] = 1;
		for (int32_t i = 2; i < N; i ++) {
			if (!no_prime[i]) prime.emplace_back(i);
			for (int64_t j : prime) {
				if (i * j >= N) break;
				no_prime[i * j] = 1;
				if (i % j == 0) break;
			}
		}
	}
	auto begin() { return prime.begin(); }
	const auto& begin() const { return prime.begin(); }
	auto end() { return prime.end(); }
	const auto& end() const { return prime.end(); }
	const auto operator [] (int idx) const { return !no_prime[idx]; }
};

// 线性筛求欧拉函数
template <int N, typename T1 = int32_t, typename T2 = int32_t>
struct Euler_phi {
	std::vector<T1> prime;
	std::bitset<N> no_prime;
	std::array<T2, N> phi;
	Euler_phi() : phi{}, no_prime{} {
		no_prime[0] = no_prime[1] = 1;
		phi[1] = 1;
		for (int32_t i = 2; i < N; i ++) {
			if (!no_prime[i]) {
				prime.emplace_back(i);
				phi[i] = T2{i - 1};
			}
			for (int64_t j : prime) {
				if (i * j >= N) break;
				no_prime[i * j] = 1;
				if (i % j) {
					phi[i * j] = phi[i] * phi[j];
				} else {
					phi[i * j] = phi[i] * j;
					break;
				}
			}
		}
	}
	auto begin() { return prime.begin(); }
	const auto& begin() const { return prime.begin(); }
	auto end() { return prime.end(); }
	const auto& end() const { return prime.end(); }
	const auto operator [] (int idx) const { return !no_prime[idx]; }
};

// 线性筛求最小素因子
template <int N, typename T1 = int32_t, typename T2 = int32_t>
struct Euler_pr {
	std::vector<T1> prime;
	std::bitset<N> no_prime;
	std::array<T2, N> pr;
	Euler_pr() : pr{}, no_prime{} {
		no_prime[0] = no_prime[1] = 1;
		pr[0] = pr[1] = 1;
		for (int32_t i = 2; i < N; i ++) {
			if (!no_prime[i]) {
				prime.emplace_back(i);
				pr[i] = T2{i};
			}
			for (int64_t j : prime) {
				if (i * j >= N) break;
				no_prime[i * j] = 1;
				pr[i * j] = j;
				if (i % j == 0) break;
			}
		}
	}
	auto begin() { return prime.begin(); }
	const auto& begin() const { return prime.begin(); }
	auto end() { return prime.end(); }
	const auto& end() const { return prime.end(); }
	const auto operator [] (int idx) const { return !no_prime[idx]; }
};