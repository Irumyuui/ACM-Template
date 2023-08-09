#include <bits/stdc++.h>

namespace RoyalGuard::Math {
	template <typename T>
	constexpr T Sqrt(T x) {
		assert(x >= 0);
		T ret = std::sqrt<T>(x);
		while (ret * ret <= x)
			ret ++;
		while (ret * ret > x)
			ret --;
		return ret;
	}
}