#include <bits/stdc++.h>

namespace __Rgs_SegTree {
	template <typename T>
	concept __Info = requires(T a, T b) {
		std::same_as<decltype(a.ok), bool>;
		{a + b} -> std::same_as<T>;
	};
	template <typename Func, typename RetT, typename T>
	concept __InitFunc = requires(Func init_func, T value) {
		{init_func(value)} -> std::convertible_to<RetT>;
	};
	template <typename T>
	concept __Arr = requires(T a, int idx) {
		{a[idx]};
	};
	template <typename Func, typename T1, typename T2>
	concept __OptFunc = requires(Func func, T1 a, T2 b) {
		{func(a, b)} -> std::same_as<T1>;
	};

	template <__Info Info>
	struct SegmentTree {
		std::vector<Info> seg;
		int n;

		SegmentTree(int _n, const Info &v)
			: seg(_n * 4, v), n(_n) {}
		
		template <typename T, __Arr Arr, __InitFunc<Info,T> Trans>
		auto build(const Arr &a, const Trans &trans_func) -> void {
			auto dfs = [&](auto &&self, int l, int r, int id) -> void {
				if (l == r) {
					seg[id] = trans_func(a[l]);
				} else {
					int mid = l + ((r - l) >> 1);
					self(self, l, mid, id * 2);
					self(self, mid + 1, r, id * 2 + 1);
					seg[id] = seg[id * 2] + seg[id * 2 + 1];
				}
		};
			dfs(dfs, 1, n, 1);
		}

		template <typename T, __OptFunc<Info, T> OptFunc>
		auto modify(int _l, int _r, const T &d, const OptFunc &opt_func) -> bool {
			auto dfs = [&](auto &&self, int l, int r, int id, int ml, int mr) -> bool {
				if (seg[id].ok == true)
					return true;
				if (l == ml && r == mr) {
					if (l == r) {
						seg[id] = opt_func(seg[id], d);
					} else {
						int mid = l + ((r - l) >> 1);
						if (seg[id * 2].ok == false)
							self(self, l, mid, id * 2, ml, mid);
						if (seg[id * 2 + 1].ok == false)
							self(self, mid + 1, r, id * 2 + 1, mid + 1, mr);
						seg[id] = seg[id * 2] + seg[id * 2 + 1];
					}
					return seg[id].ok;
				}  else {
					int mid = l + ((r - l) >> 1);
					bool ret = false;
					if (mr <= mid) {
						ret = self(self, l, mid, id * 2, ml, mr);
					} else if (ml > mid) {
						ret = self(self, mid + 1, r, id * 2 + 1, ml, mr);
					} else {
						ret = self(self, l, mid, id * 2, ml, mid);
						ret = self(self, mid + 1, r, id * 2 + 1, mid + 1, mr) && ret;
					}
					seg[id] = seg[id * 2] + seg[id * 2 + 1];
					return ret;
				}
			};
			return dfs(dfs, 1, n, 1, _l, _r);
		}

		auto query(int _l, int _r) -> Info {
			auto dfs = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
				if (l == ql && r == qr) {
					return seg[id];
				} else {
					int mid = l + ((r - l) >> 1);
					if (qr <= mid) {
						return self(self, l, mid, id * 2, ql, qr);
					} else if (ql > mid) {
						return self(self, mid + 1, r, id * 2 + 1, ql, qr);
					} else {
						return self(self, l, mid, id * 2, ql, mid) + self(self, mid + 1, r, id * 2 + 1, mid + 1, qr);
					}
				}
			};
			return dfs(dfs, 1, n, 1, _l, _r);
		};
	};
}
using __Rgs_SegTree::SegmentTree;