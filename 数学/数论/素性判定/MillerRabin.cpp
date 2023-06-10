#include <bits/stdc++.h>

namespace MillerRabin {
	using i64 = int64_t;
	using u64 = uint64_t;
	using i128 = __int128_t;

	constexpr auto Mul(i64 a, i64 b, i64 m) noexcept -> i64 {
		return static_cast<i128>(a) * b % m;
	}

	constexpr auto Power(i64 a, i64 b, i64 m) noexcept -> i64 {
		i64 ret = 1 % m;
		for (; b; b >>= 1, a = Mul(a, a, m)) 
			if (b & 1)
				ret = Mul(ret, a, m);
		return ret;
	}

	constexpr auto IsPrime(i64 n) noexcept -> bool {
		if (n < 2)
			return false;
		constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
		int s = std::countr_zero<u64>(n - 1);
		i64 d = (n - 1) >> s;
		for (auto a : A) {
			if (a == n) 
				return true;
			i64 x = Power(a, d, n);
			if (x == 1 || x == n - 1) 
				continue;
			bool ok = false;
			for (int i = 0; i < s - 1; i ++) {
				x = Mul(x, x, n);
				if (x == n - 1) {
					ok = true;
					break;
				}
			}
			if (!ok)
				return false;
		}
		return true;
	}
}