#include <bits/stdc++.h>

// template <typename Info, typename Seg_merge = Info(*)(const Info&, const Info&)>
// struct SegTree {
// 	struct Node {
// 		Info val;
// 	};
// 	int n;
// 	Seg_merge merge_func;
// 	std::vector<Node> seg;

// 	SegTree(int _size, const Info &base_val, const Seg_merge &merge_func) : n(_size), merge_func(merge_func), seg(_size * 4, {base_val}) {}

// 	// template <typename TagetType, typename TagetArr = std::vector<TagetType>, typename Init = Info(*)(TagetType)>
// 	// SegTree(int _size, const Info &base_val, const Seg_merge &merge_func, const TagetArr &a, const Init &init_func) : seg(_size * 4, base_val), n(_size), merge_func(merge_func) {
// 	// 	build(a, init_func);
// 	// }	

// 	void rise(int id) {
// 		// seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
// 		seg[id].val = merge_func(seg[id * 2].val, seg[id * 2 + 1].val);
// 	}

// 	template <typename TagetType, typename TagetArr = std::vector<TagetType>, typename Init = Info(*)(TagetType)>
// 	void build(const TagetArr &a, const Init &init_func) {
// 		auto build = [&](auto &&dfs, int l, int r, int id) -> void {
// 			if (l == r) {
// 				seg[id].val = init_func(a[l]);
// 			} else {
// 				int mid = l + ((r - l) >> 1);
// 				dfs(dfs, l, mid, id * 2);
// 				dfs(dfs, mid + 1, r, id * 2 + 1);
// 				rise(id);
// 			}
// 		};
// 		build(build,1,n,1);
// 	}

// 	template <typename Ctype, typename Cinit = void(*)(Info&,Ctype)>
// 	void change(int tag, const Ctype &c_val, const Cinit &cinit_func) {
// 		auto change = [&](auto &&dfs, int l, int r, int id) -> void {
// 			if (l == r) {
// 				cinit_func(seg[id].val, c_val);
// 			} else {
// 				int mid = l + ((r - l) >> 1);
// 				if (tag <= mid)
// 					dfs(dfs, l, mid, id * 2);
// 				else
// 					dfs(dfs, mid + 1, r, id * 2 + 1);
// 				rise(id);
// 			}
// 		};
// 		change(change, 1, n, 1);
// 	}

// 	Info query(int ql, int qr) {
// 		auto query = [&](auto &&dfs, int l, int r, int id, int ql, int qr) -> Info {
// 			if (l == ql && r == qr)
// 				return seg[id].val;
// 			int mid = l + ((r - l) >> 1);
// 			if (qr <= mid)
// 				return dfs(dfs, l, mid, id * 2, ql, qr);
// 			else if (ql > mid)
// 				return dfs(dfs, mid + 1, r, id * 2 + 1, ql, qr);
// 			else 
// 				return dfs(dfs, l, mid, id * 2, ql, mid) + dfs(dfs, mid + 1, r, id * 2 + 1, mid + 1, qr);
// 		};
// 		return query(query,1,n,1,ql,qr);
// 	}
// };

template <typename Info = int64_t, typename Merge = std::plus<Info>>
struct SegTree {
	struct Node {
		Info val;
	};
	int n;
	Merge merge;
	std::vector<Node> seg;
	
	explicit SegTree(int _size, const Info &init_val, const Merge &_merge) : n(_size), merge(_merge), seg(_size * 4, init_val) {}
	
	void rise(int id) {
		seg[id].val = merge(seg[id * 2].val, seg[id * 2 + 1].val);
	}

	template <typename Array, typename InitFunc = decltype([](const auto &val) -> Info { return Info{val}; })>
	void build(const Array &a, const InitFunc &init_func) {
		auto build = [&](auto &&dfs, int l, int r, int id) -> void {
			if (l == r) {
				seg[id].val = init_func(a[l]);
			} else {
				int mid = l + (r - l) / 2;
				dfs(dfs, l, mid, id*2);
				dfs(dfs, mid + 1, r, id * 2 + 1);
				rise(id);
			}
		};
		build(build, 1, n, 1);
	}

	template <typename Opt = decltype([](Info &node) -> void {})>
	void change(int tag, const Opt &opt) {
		auto change = [&](auto &&dfs, int l, int r, int id) -> void {
			if (l == r) {
				opt(seg[id].val);
			} else {
				int mid = l + (r - l) / 2;
				if (tag <= mid) {
					dfs(dfs, l, mid, id * 2);
				} else {
					dfs(dfs, mid + 1, r, id * 2 + 1);
				}
				rise(id);
			}
		};
		change(change, 1, n, 1);
	}

	Info query(int _ql, int _qr) {
		auto query = [&](auto &&dfs, int l, int r, int id, int ql, int qr) -> Info {
			if (l == ql && r == qr) {
				return seg[id].val;
			} else {
				int mid = l + (r - l) / 2;
				if (qr <= mid) {
					return dfs(dfs, l, mid, id * 2, ql, qr);
				} else if (ql > mid) {
					return dfs(dfs, mid + 1, r, id * 2 + 1, ql, qr);
				} else {
					return merge(
						dfs(dfs, l, mid, id * 2, ql, mid),
						dfs(dfs, r, mid + 1, r, id * 2 + 1, mid + 1, qr)
					);
				}
			}
		};
		return query(query, 1, n, 1, _ql, _qr);
	}
};