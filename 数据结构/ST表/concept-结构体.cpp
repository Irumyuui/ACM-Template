#include <bits/stdc++.h>

namespace __SparseTable {

template <typename MergeFunc, typename T>
concept __MergeFunc = requires(MergeFunc func, T a, T b) {
	{func(a, b)} -> std::same_as<T>;
};
template <typename Arr>
concept __Arr = requires(Arr a, int idx) {
	{a[idx]};
};

template <typename T, __MergeFunc<T> MergeFunc>
struct SparseTable {
	std::vector<std::vector<T>> f;
	MergeFunc merge;
	int n;

	SparseTable(int _n, const T &init_v, const MergeFunc merge_func) : f(std::__lg(_n) + 1, std::vector<T>(_n + 1, init_v)), n(_n), merge(merge_func) {}
	
	template <__Arr Arr>
	void build(const Arr &a) {
		for (int i = 1; i <= n; i ++)
			f[0][i] = a[i];
		for (int i = 1; i <= std::__lg(n); i ++) 
			for (int j = 1; j + (1 << i) - 1 <= n; j ++)
				f[i][j] = merge(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
	}
	T query(int l, int r) {
		int s = std::__lg(r - l + 1);
		return merge(f[s][l], f[s][r - (1 << s) + 1]);
	}
};

}