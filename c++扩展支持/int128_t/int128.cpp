#include <bits/stdc++.h>

namespace ioInt128 {
	inline constexpr auto abs(const __int128_t &a) noexcept -> __int128_t {
		return a < 0 ? -a : a;
	}
	inline constexpr auto gcd(const __int128_t &a, const __int128_t &b) noexcept -> __int128_t {
		return [&](auto &&func) noexcept -> __int128_t {
			return func(func, abs(a), abs(b));
		} (
			[](auto &&self, __int128_t a, __int128_t b) noexcept -> __int128_t {
				if (b == 0) {
					return a;
				} else {
					return self(self, b, a % b);
				}
			}
		);
	}
	inline constexpr auto operator << (std::ostream &out, const __int128_t &v) noexcept -> std::ostream& {
		if (v < 0) {
			out << '-';
		} else if (v == 0) {
			out << 0;
			return out;
		}
		auto to_print = [&](auto &&self, const __int128_t &v) constexpr -> void {
			if (v >= 10) {
				self(self, v / 10);
			}
			out << int32_t(v % 10);
		};
		to_print(to_print, abs(v));
		return out;
	}
	inline auto operator >> (std::istream &in, __int128_t &v) noexcept -> std::istream& {
		std::string s;
		in >> s;
		v = 0;
		int i, f;
		if (s.front() == '-') {
			i = 1, f = -1;
		} else {
			i = 0, f = 1;
		}
		for (int n = s.size(); i < n; i ++) {
			v *= 10;
			v += s[i] - '0';
		}
		v *= f;
		return in;
	}
};
using namespace ioInt128;
using i128 = __int128_t;
using ill = __int128_t;