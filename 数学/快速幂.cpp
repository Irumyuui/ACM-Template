#include <bits/stdc++.h>

constexpr auto qp(int64_t a, int64_t i, int64_t p) -> int64_t {
	int64_t ret = 1 % p;
	a %= p;
	for (; i > 0; i >>= 1, (a *= a) %= p) 
		if (i % 2)
			(ret *= a) %= p;
	return ret;
}
constexpr auto qp(int64_t a, int64_t i) -> int64_t {
	int64_t ret = 1;
	for (; i > 0; i >>= 1, a *= a)
		if (i % 2)
			ret *= a;
	return ret;
}

int main() {

}