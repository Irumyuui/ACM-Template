#include <bits/stdc++.h>

namespace __SegTree {

template <typename T>
concept __Info = requires(T a, T b) {
	{a + b} -> std::same_as<T>;
};
template <typename Func, typename RetT, typename T>
concept __InitFunc = requires(Func init_func, T value) {
	{init_func(value)} -> std::same_as<RetT>;
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
	
	SegmentTree(int _n, const Info &v) : seg(_n * 4, v), n(_n) {}

	template <typename T, __Arr Arr, __InitFunc<Info,T> Trans>
	void build(const Arr &a, const Trans &trans_func) {
		static auto dfs = [&](auto &&self, int l, int r, int id) -> void {
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

	template <typename T, __OptFunc<Info,T> OptFunc>
	void change(int tag, T d, const OptFunc &opt_func) {
		static auto dfs = [&](auto &&self, int l, int r, int id) -> void {
			if (l == r) {
				seg[id] = opt_func(seg[id], d);
			} else {
				int mid = l + ((r - l) >> 1);
				if (tag <= mid) {
					self(self, l, mid, id * 2);
				} else {
					self(self, mid + 1, r, id * 2 + 1);
				}
				seg[id] = seg[id * 2] + seg[id * 2 + 1];
			}
		};
		dfs(dfs, 1, n, 1);
	}

	Info query(int _ql, int _qr) {
		static auto dfs = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
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
		return dfs(dfs, 1, n, 1, _ql, _qr);
	}
};

} // segment tree