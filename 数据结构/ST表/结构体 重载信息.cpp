#include <bits/stdc++.h>

namespace Data_Structure_SparseTable {
	namespace __DS_ST_SP {
		template <typename Ret>
		struct Translate {
			template <typename Val>
				requires requires(Val v) { {Ret{v}}; }
			constexpr auto operator () (const Val &v) const -> Ret {
				return Ret{v};
			}
		};
	}

	template <typename Info>
		requires requires(Info a, Info b) { {a + b} -> std::convertible_to<Info>; }
	struct SparseTable {
		int n;
		std::vector<std::vector<Info>> f;

		explicit SparseTable(int _n, const Info &__init_v = Info{}) 
			: n(_n), f(std::__lg(_n) + 1, std::vector<Info>(_n + 1, __init_v)) {}

		template <typename T, typename Container, typename Transfrom = __DS_ST_SP::Translate<Info>>
			requires requires(Container a, int idx, T b, Transfrom func) {
				{a[idx]} -> std::convertible_to<T>;
				{func(b)} -> std::convertible_to<Info>;
			}
		auto init(const Container &a, const Transfrom &trans = Transfrom{}) -> void {
			for (int i = 1; i <= n; i ++) {
				f[0][i] = trans(a[i]);
			}
		}

		auto build() -> void {
			for (int i = 1; i <= std::__lg(n); i ++)
				for (int j = 1; j + (1 << i) - 1 <= n; j ++)
					f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << (i - 1))];
		}

		auto query(int l, int r) -> Info {
			int s = std::__lg(r - l + 1);
			return f[s][l] + f[s][r - (1 << s) + 1];
		}
	};
}
using Data_Structure_SparseTable::SparseTable;