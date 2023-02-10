#include <bits/stdc++.h>

template <typename T, typename Func = T(*)(T,T)>
struct SparseTable {
	int n;
	std::vector<std::vector<T>> f;
	Func func;
	explicit SparseTable(int _n, T &&_val, const Func &_func) : f(std::__lg(n) + 1, std::vector<T>(n + 1, _val)), n(_n), func(_func) {} 
	template <typename Arr> explicit SparseTable(int _n, T &&_val, const Arr &a, const Func &_func) : n(_n), f(std::__lg(_n + 1) + 1, std::vector<T>(n + 1, _val)), func(_func) {
		build(a);
	}
	template <typename Arr> constexpr auto build(const Arr &a) -> void {
		for (int i = 1; i <= n; i ++) {
			f[0][i] = a[i];
		}
		for (int i = 1; i <= std::__lg(n); i ++) {
			for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
				f[i][j] = func(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	auto query(int l, int r) -> T {
		int s = std::__lg(r - l + 1);
		return func(f[s][l], f[s][r - (1 << s) + 1]);
	}
};

int main() {

}