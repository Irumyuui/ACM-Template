#include <bits/stdc++.h>

template <typename T>
concept integral = std::is_integral_v<T>;

template <integral T>
constexpr T gcd(T a, T b) {
	static __gcd = [](auto &&__d_gcd T _a, T _b) -> T {
		if (_b == 0)
			return _a;
		return __d_gcd(_b, _a % _b);
	};
	return __gcd(__gcd, std::abs<T>(a), std::abs<T>(b));
}