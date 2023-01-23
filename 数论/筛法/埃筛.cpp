#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

const int N = 1e6 + 10;
std::vector<int> prime;
std::bitset<N> no_prime;

void init() {
	no_prime[0] = no_prime[1] = 1;
	for (int i = 2; i < N; i ++) {
		if (!no_prime[i]) {
			prime.emplace_back(i);
			for (int64_t j = int64_t(i) * 2; j < N; j += i) {
				no_prime[j] = 1;
			}
		}
	}
}

template <int N, typename T = int32_t>
struct Eratos {
	std::vector<T> prime;
	std::bitset<N> no_prime;
	Eratos() {
		no_prime[0] = no_prime[1] = 1;
		for (int i = 2; i < N; i ++) {
			if (!no_prime[i]) {
				prime.emplace_back(i);
				for (int64_t j = int64_t(i) * 2; j < N; j += i)
					no_prime[j] = 1;
			}
		}
	}
	auto begin() { return prime.begin(); }
	const auto& begin() const { return prime.begin(); }
	auto end() { return prime.end(); }
	const auto& end() const { return prime.end(); }
	const auto operator [] (int idx) const { return !no_prime[idx]; }
};

Eratos<10> pri;

int main() {
	for (auto i : pri) {
		cout << i << ' ';
	}
	cout << pri[2] << '\n';
}