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
template <typename Translate, typename RetT, typename T>
concept __Translate = requires(Translate func, T a) {
	{func(a)} -> std::same_as<RetT>;
};

template <typename T, __MergeFunc<T> MergeFunc>
struct SparseTable {
	std::vector<std::vector<T>> f;
	MergeFunc merge;
	int n;

	SparseTable(int _n, const T &init_v, const MergeFunc merge_func) : f(std::__lg(_n) + 1, std::vector<T>(_n + 1, init_v)), n(_n), merge(merge_func) {}
	
	template <typename Ty, __Arr Arr, __Translate<T, Ty> Translate>
	void build(const Arr &a, const Translate &trans) {
		for (int i = 1; i <= n; i ++)
			f[0][i] = trans(a[i]);
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
// using __SparseTable::SparseTable;

namespace Royal_Guard::Data_Structure::Requires_DS::Merge_Init_SparseTable {
	template <typename Info_Merge, typename Info>
	concept Info_Meege_Func = requires(Info_Merge func, Info a, Info b) {
		{func(a, b)} -> std::convertible_to<Info>;
	};
	template <typename T_Container, typename T>
	concept Type_Container = requires(T_Container a, int idx) {
		{a[idx]} -> std::convertible_to<T>;
	};
	template <typename Transform, typename Tag_Type, typename Type>
	concept Transform_Func = requires(Transform func, Type a) {
		{func(a)} -> std::convertible_to<Tag_Type>;
	};
	
	template <typename Info, Info_Meege_Func<Info> Merge>
	struct SparseTable {
		int n;
		Merge merge;
		std::vector<std::vector<Info>> f;

		SparseTable(int _n, const Info &init_v, const Merge &merge_func) 
			: n(_n), merge(merge_func), f(std::__lg(_n) + 1, std::vector<Info>(_n + 1, init_v)) {}

		template <typename T, Type_Container<T> Container, Transform_Func<Info, T> Transfrom>
		auto init(const Container &a, const Transfrom &trans) -> void {
			for (int i = 1; i <= n; i ++) 
				f[0][i] = trans(a[i]);
		}

		auto build() -> void {
			for (int i = 1; i <= std::__lg(n); i ++)
				for (int j = 1; j + (1 << i) - 1 <= n; j ++)
					f[i][j] = merge(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}

		auto query(int l, int r) -> Info {
			int s = std::__lg(r - l + 1);
			return merge(f[s][l], f[s][r - (1 << s) + 1]);
		}
	};
}
using Royal_Guard::Data_Structure::Requires_DS::Merge_Init_SparseTable::SparseTable;