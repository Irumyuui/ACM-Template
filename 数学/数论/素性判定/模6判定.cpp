#include <bits/stdc++.h>
using namespace std;

bool __is_prime(int64_t n) {
	if (n == 2 || n == 3 || n == 5) return true;
	if (n <= 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;
	for (int64_t i = 5; i * i <= n; i += 6) 
		if (n % i == 0 || n % (i + 1) == 0)
			return false;
	return true;
}

constexpr auto is_prime(int64_t n) noexcept -> bool {
	if (n == 2 || n == 3 || n == 5) 
		return true;
	if (n <= 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
		return false;
	for (int64_t i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 1) == 0)
			return false;
	return true;
}

auto Solve() -> void {
	for (auto i : std::views::iota(1, 100)
				| std::views::filter([](const auto &n) -> bool {
						if (n == 2 || n == 3 || n == 5) 
							return true;
						if (n <= 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
							return false;
						for (int64_t i = 5; i * i <= n; i += 6)
							if (n % i == 0 || n % (i + 1) == 0)
								return false;
						return true;
					})
	) {
		cout << i << ' ';
	}
}

int main() {
	
}