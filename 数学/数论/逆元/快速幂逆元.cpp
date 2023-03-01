#include <bits/stdc++.h>

using ll = int64_t;

constexpr ll MOD = 1e9 + 7;

constexpr ll qpow(ll a, ll i, ll p) {
	a %= p;
	ll ret = 1 % p;
	while (i > 0) {
		if (i & 1) {
			(ret *= a) %= p;
		}
		(a *= a) %= p;
		i >>= 1;
	}
	return ret;
}

constexpr ll inv(ll a, ll p) {
	return qpow(a, p - 2, p);
}