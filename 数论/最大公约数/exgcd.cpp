#include <bits/stdc++.h>

template <typename type>
concept integral = std::is_integral_v<type>;

template <integral type>
std::array<type,3> exgcd(type _a, type _b) {
	auto __exgcd = [&](auto &&self, type a, type b) -> std::array<type,3> {
		if (b == 0) {
			return {a, type{1}, type{0}};
		} else {
			auto [d, x, y] = self(self, b, a % b);
			return {d, y, x - a / b * y};
		}
	};
	return __exgcd(__exgcd, std::abs<type>(_a), std::abs<type>(_b));
}

template <integral type>
type inv(type a, type mod) {
	auto [_, a_inv, __] = exgcd(a, mod);
	a_inv %= mod;
	if (a_inv < mod) a_inv += mod;
	return a_inv;
}