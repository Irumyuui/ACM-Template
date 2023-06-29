#include <bits/stdc++.h>

namespace RoyalGuard::Math::Trickster {
	template <std::integral Integral>
	constexpr auto IsPrime(Integral n) noexcept -> bool {
		if (n <= 1)
			return false;
		if (n == 2 || n == 3 || n == 5)
			return true;
		if (n % 6 != 1 &&  n % 6 != 5)
			return false;
		for (Integral i = 5; i * i <= n; i += 6)
			if (n % i == 0 || n % (i + 2) == 0)
				return false;
		return true;
	}
}