#include <bits/stdc++.h>

namespace RoyalGuard::DataStructure
{
	template <typename OperatorFunc, typename Type>
	concept OperatorFuncAbleType = requires(Type a, Type b, OperatorFunc opt) {
		{opt(a, b)} -> std::same_as<Type>;
	};

	template <typename Container, typename Type>
	concept IsContainer = requires(Container container, int idx, Type value) {
		{container[idx] = value};
	};

	template <typename Info, OperatorFuncAbleType<Info> MergeOpt = std::plus<Info>>
	class SegmentTree {
		public:
			explicit SegmentTree(int size, MergeOpt mergeOpt = MergeOpt{}) : seg(size * 4), mergeOpt(mergeOpt), n(size) {

			}

			explicit SegmentTree(const std::vector<Info> &vec, MergeOpt mergeOpt = MergeOpt{}) : SegmentTree(vec.size(), mergeOpt) {
				Build(vec, [](auto &&value) -> Info { return value; });
			}

		private:
			void Rise(int id) {
				seg[id] = mergeOpt(seg[id * 2], seg[id * 2 + 1]);
			}

		public:
			template <typename Container, typename ConvertOperator>
			requires requires(Container container, int idx, ConvertOperator convert) {
				{convert(container[idx])} -> std::same_as<Info>;
				{std::size(container)};
			} void Build(const Container &con, ConvertOperator convert = ConvertOperator{}) {
				assert(std::size(con) >= n);
				auto func = [&](auto &&self, int l, int r, int id) -> void {
					if (l + 1 == r) {
						seg[id] = convert(con[l]);
					} else {
						int mid = l + ((r - l) >> 1);
						self(self, l, mid, id * 2);
						self(self, mid, r, id * 2 + 1);
						Rise(id);
					}
				};
				func(func, 0, n, 1);
			}

			template <OperatorFuncAbleType<Info> UpdateOpt>
			void Update(int target, Info dx, UpdateOpt updateOpt) {
				assert(0 <= target && target < n);
				auto func = [&](auto &&self, int l, int r, int id) -> void {
					if (l + 1 == r) {
						seg[id] = updateOpt(seg[id], dx);
					} else {
						auto mid = l + ((r - l) >> 1);
						if (target < mid) {
							self(self, l, mid, id * 2);
						} else {
							self(self, mid, r, id * 2 + 1);
						}
						Rise(id);
					}
				};
				func(func, 0, n, 1);
			}

			Info Query(int L, int R) {
				assert(L < R && 0 <= L && L < n && 0 < R && R <= n);
				auto func = [&](auto &&self, int l, int r, int id, int ql, int qr) -> Info {
					if (l == ql && r == qr) {
						return seg[id];
					} else {
						int mid = l + ((r - l) >> 1);
						if (qr <= mid) {
							return self(self, l, mid, id * 2, ql, qr);
						} else if (ql >= mid) {
							return self(self, mid, r, id * 2 + 1, ql, qr);
						} else {
							return mergeOpt(
								self(self, l, mid, id * 2, ql, mid),
								self(self, mid, r, id * 2 + 1, mid, qr)
							);
						}
					}
				};
				return func(func, 0, n, 1, L, R);
			}
			
		private:
			std::vector<Info> seg;
			MergeOpt mergeOpt;
			const int n;
	};
}


template <typename Info, typename MergeOpt = std::plus<Info>>
class SegmentTree {
	public:
		explicit SegmentTree(int size, Info initValue = Info{}, MergeOpt mergeOpt = MergeOpt{})
			: segTree(size * 4, initValue), mergeOpt{mergeOpt}, initValue{initValue}, N{size - 1} {}
	
		template <typename Container, typename Translate>
		void Build(Container &&con, Translate &&translate) {
			auto func = [&](auto &&self, int l, int r, int id) -> void {
				if (l == r) {
					segTree[id] = translate(con[id]);
				} else {
					int mid = l + ((r - l) >> 1);
					self(self, l, mid, id * 2 + 1);
					self(self, mid + 1, r, id * 2 + 2);
					Rise(id);
				}
			};
			func(func, 0, N, root);
		}

		template <typename Type, typename Translate>
		void Update(int target, Type value, Translate translate) {
			auto func = [&](auto &&self, int l, int r, int id) -> void {
				if (l == r) {
					segTree[id] = translate(segTree[id], value);
				} else {
					int mid = l + ((r - l) >> 1);
					if (target <= mid) {
						self(self, l, mid, id * 2 + 1);
					} else {
						self(self, mid + 1, r, id * 2 + 2);
					}
				}
			};
			func(func, 0, N, root);
		}

		Info RangeQuery(int rgl, int rgr) {
			if (rgl >= rgr) {
				return initValue;
			}
			return RangeQuery(0, N, root, rgl, rgr - 1);
		}

	private:
		void Rise(int id) {
			segTree[id] = mergeOpt(segTree[id * 2 + 1], segTree[id * 2 + 2]);
		}

		Info RangeQuery(int l, int r, int id, int ql, int qr) {
			if (l == ql && r == qr) {
				return segTree[id];
			} else {
				int mid = l + ((r - l) >> 1);
				if (qr <= mid) {
					return RangeQuery(l, mid, id * 2 + 1, ql, qr);
				} else if (ql > mid) {
					return RangeQuery(mid + 1, r, id * 2 + 2, ql, qr);
				} else {
					return mergeOpt(RangeQuery(l, mid, id * 2 + 1, ql, mid), RangeQuery(mid + 1, r, id * 2 + 2, mid + 1, qr));
				}
			}
		}

	private:
		constexpr static int root = 0;
		std::vector<Info> segTree;
		MergeOpt mergeOpt;
		const Info initValue;
		const int N;
};