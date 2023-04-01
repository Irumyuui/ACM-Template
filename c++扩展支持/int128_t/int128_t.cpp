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
}