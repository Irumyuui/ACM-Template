#include <bits/stdc++.h>

namespace __SegTree {

	namespace Support {
		template <typename Value>
		struct Max_Val {
			Value val;
			
			Max_Val(Value val = Value{}) : val{val} {}

			friend Max_Val operator + (const Max_Val &a, const Max_Val &b) {
				return Max_Val{
					std::max<Value>(a.val, b.val),
				};
			}
		};
		
		template <typename Value>
		struct Min_Val {
			Value val;
			
			Min_Val(Value val = Value{}) : val{val} {}

			friend Min_Val operator + (const Min_Val &a, const Min_Val &b) {
				return Min_Val{
					std::min<Value>(a.val, b.val),
				};
			}
		};

		template <typename Value>
		struct Add_Val {
			Value val;

			Add_Val(Value val = Value{}) : val{val} {}

			friend Add_Val operator + (const Add_Val &a, const Add_Val &b) {
				return Add_Val{
					a.val + b.val,
				};
			}
		};
	}

	// segment merge
	template <typename T>
	concept __Info = requires(T a, T b) {
		{a + b} -> std::same_as<T>;
	};

	// T convertible able
	template <typename Func, typename RetT, typename T>
	concept __InitFunc = requires(Func init_func, T value) {
		{init_func(value)} -> std::convertible_to<RetT>;
	};

	// container
	template <typename T>
	concept __Arr = requires(T a, int idx) {
		{a[idx]};
	};

	// operator support
	template <typename Func, typename T1, typename T2>
	concept __OptFunc = requires(Func func, T1 a, T2 b) {
		{func(a, b)} -> std::same_as<T1>;
	};

	/**
	 * @brief Segment tree with single point of modification support
	 * @tparam Info Requires friend Info operator +
	 */
	template <__Info Info>
	struct SegmentTree {
		std::vector<Info> seg;
		int n;
		
		/**
		 * @brief Segment Tree init
		 * @param _n Range of interval [1, n]
		 * @param v Initial value of Info
		 */
		SegmentTree(int _n, const Info &v)
			: seg(_n * 4, v), n(_n) {}

		/**
		 * @brief Build a Segment Tree
		 * @tparam T Type of elements in container
		 * @tparam Arr Container's Type
		 * @tparam Trans Convert T to Info
		 * @param a Container
		 * @param trans_func Convert function
		 */
		template <typename T, __Arr Arr, __InitFunc<Info,T> Trans>
		void build(const Arr &a, const Trans &trans_func) {
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

		/**
		 * @brief Single point modification
		 * @tparam T Type of value
		 * @tparam OptFunc Operation
		 * @param tag Modified position
		 * @param d Modified value
		 * @param opt_func Info opt(Info, T)
		 */
		template <typename T, __OptFunc<Info,T> OptFunc>
		void change(int tag, T d, const OptFunc &opt_func) {
			auto dfs = [&](auto &&self, int l, int r, int id) -> void {
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
			return dfs(dfs, 1, n, 1, _ql, _qr);
		}
	};

} // segment tree
using __SegTree::SegmentTree;