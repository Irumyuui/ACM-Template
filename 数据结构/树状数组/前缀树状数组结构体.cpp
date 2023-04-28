#include <bits/stdc++.h>

namespace Trickster {
	template <typename _Tp, typename _Operator = std::plus<_Tp>>
	requires requires(const _Tp a, _Tp b, _Operator op) {
		{op(a, b)} -> std::convertible_to<_Tp>;
	} class PrefixFenwickTree {
		public:
			using Type = _Tp;
			using Operator = _Operator;

		private:
			constexpr static std::size_t Lowbit(std::size_t x) noexcept {
				return x & -x;
			}

		public:
			explicit PrefixFenwickTree(std::size_t _n, Type &&initValue = {}, const Operator &opt = Operator{})
				: bit(_n + 1, initValue), n{_n}, opt{opt} {}

			void Assign(std::size_t _n, const Type &value) {
				n = _n;
				bit.Assign(_n + 1, value);
			}

			void Set(std::size_t pos, Type &&value) {
				for (std::size_t i = pos; i <= n; i += Lowbit(i)) {
					bit[i] = opt(bit[i], value);
				}
			}

			Type Get(std::size_t pos, Type result = Type{}) const {
				for (std::size_t i = pos; i > 0; i -= Lowbit(i)) {
					result = opt(result, bit[i]);
				}
				return result;
			}

			Type& operator [] (std::size_t pos) {
				return bit[pos];
			}
			const Type& operator [] (std::size_t pos) const {
				return bit[pos];
			}

		private:
			std::vector<Type> bit;
			std::size_t n;
			const Operator opt;
	};
}

using Trickster::PrefixFenwickTree;

template <typename _Tp, typename _Operator>
using FenwickTree = Trickster::PrefixFenwickTree<_Tp, _Operator>;