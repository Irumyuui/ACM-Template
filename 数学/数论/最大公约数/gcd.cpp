#include <bits/stdc++.h>

template <typename T>
concept integral = std::is_integral_v<T>;

template <integral T>
constexpr T gcd(T a, T b) {
	auto __gcd = [](auto &&__d_gcd, T _a, T _b) -> T {
		if (_b == 0)
			return _a;
		return __d_gcd(_b, _a % _b);
	};
	return __gcd(__gcd, std::abs<T>(a), std::abs<T>(b));
}

template <typename T>
	requires std::is_integral_v<T>
constexpr auto __Gcd(T a, T b) -> T {
	if (a == 0)
		return a;
	if (b == 0)
		return b;
	if (a % 2 == 0 && b % 2 == 0)
		return 2 * __Gcd(a / 2, b / 2);
	else if (a % 2 == 0)
		return __Gcd(a / 2, n);
	else if (b % 2 == 0)
		return __Gcd(a, b / 2);
	else
		return __Gcd(std::abs(a - b), std::min(a, b));
}

template <typename T>
	requires std::is_integral_v<T>
constexpr auto Gcd(T a, T b) -> T {
	return __Gcd(std::abs(a), std::abs(b));
}