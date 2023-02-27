#include <bits/stdc++.h>

template <typename T = long long>
constexpr auto qp(T a, T i, T ret = {1}) -> T {
	for (; i > 0; i >>= 1, a *= a) 
		if (i & 1)
			ret *= a;
	return ret;
}
template <typename T = long long>
constexpr auto qp(T a, T i, const T P, T ret = {1}) -> T {
	a %= P;
	for (; i > 0; i >>= 1, (a *= a) %= p) 
		if (i & 1)
			(ret *= a) %= p;
	return ret;
}