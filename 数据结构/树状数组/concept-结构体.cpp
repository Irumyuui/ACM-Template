#include <bits/stdc++.h>

namespace Royal_Guard::Data_Structure::Requires_DS::Fenwick_Tree {
	template <typename Transform, typename Tag_Type, typename Type>
	concept Transform_Func = requires(Transform func, Type a) {
		{func(a)} -> std::same_as<Tag_Type>;
	};
	template <typename Opt, typename Info_Type, typename Type>
	concept Opt_Func = requires(Opt func, Info_Type a, Type b) {
		{func(a, b)} -> std::same_as<Info_Type>;
	};

	template <typename Info>
	struct Fenwick_Tree {
		int n;
		std::vector<Info> bit;

		Fenwick_Tree() {}
		Fenwick_Tree(int _n, const Info &init_v = {})
			: n(_n), bit(_n + 1, init_v) {}
		
		void assign(int _n, const Info &init_v = {}) {
			n = _n;
			bit.assign(_n + 1, init_v);
		}

		template <typename T, Opt_Func<Info, T> Opt>
		auto update(int x, const T &d, const Opt &opt) -> void {
			for (int i = 1; i <= n; i ++) {
				bit[i] = opt(bit[i], d);
			}
		}

		template <Opt_Func<Info, Info> Opt>
		auto ask(int x, Info ret, const Opt &opt) -> Info {
			for (int i = x; i > 0; i -= i & -i) {
				ret = opt(ret, bit[i]);
			}
			return ret;
		}
	};
}
using Royal_Guard::Data_Structure::Requires_DS::Fenwick_Tree::Fenwick_Tree;