#include <bits/stdc++.h>

namespace Royal_Guard::IO::Int128 {
	std::istream& operator >> (std::istream &is, __int128_t &x) {
		x = 0;
		std::string s; is >> s;
		bool flag = false;
		for (auto ch : s)
			if (ch == '-') flag = true;
			else x = x * 10 + (ch ^ 48);
		if (flag) x = -x;
		return is;
	}
	std::ostream& operator << (std::ostream &os, __int128_t x) {
		if (x == 0) return os << '0';
		bool flag = false;
		if (x < 0)
			x = -x, flag = true;
		std::string s;
		while (x > 0)
			s += x % 10 + '0', x /= 10;
		if (flag) s += '-';
		std::reverse(s.begin(), s.end());
		return os << s;
	}
	using ill = __int128_t;
	using i128 = __int128_t;
}
using namespace Royal_Guard::IO::Int128;

auto operator >> (std::istream &is, __int128_t &x) -> std::istream& {
	x = 0;
	std::string s; is >> s;
	bool flag = false;
	for (auto ch : s)
		if (ch == '-') flag = true;
		else x = x * 10 + (ch ^ 48);
	if (flag) x = -x;
	return is;
}
auto operator << (std::ostream &out, __int128_t __x) noexcept -> std::ostream& {
	constexpr uint64_t base = 0x8ac7230489e80000;
	if (__x < 0) {
		out << '-';
		__x = -__x;
	}
	uint64_t x2 = __x % base;
	__x /= base;
	uint64_t x1 = __x % base;
	__x /= base;
	uint64_t x0 = __x;
	auto prev = out.fill();
	if (x0 > 0) {
		out << x0 << std::setw(19) << std::setfill('0') << x1 << std::setw(19) << std::setfill('0') << x2;
	} else if (x1 > 0) {
		out << x1 << std::setw(19) << std::setfill('0') << x2;
	} else {
		out << x2;
	}
	out.fill(prev);
	return out;
}
