#include <bits/stdc++.h>

template <typename T>
constexpr T Sqrt(const T &x) {
	T ret = std::sqrt<T>(x);
	while (ret * ret <= x) {
		ret ++;
	}
	while (ret * ret > x) {
		ret --;
	}
	return ret;
}