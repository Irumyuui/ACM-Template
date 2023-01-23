#include <bits/stdc++.h>

template <typename Type, int32_t N>
struct Dvector {
	std::vector<Type> vec;
	Dvector(int _size, const Type &init_val = {}) : vec(N + _size, init_val) {}
	auto& operator [] (const int idx) {
		return vec[idx + N];
	}
	const auto& operator [] (const int idx) {
		return vec[idx + N];
	}
};