#include <bits/stdc++.h>

namespace Trickster {
	template <typename _Tp, typename Operator>
	class FenwickTree {
	public:
		using Type = _Tp;

	private:
		constexpr static std::size_t Lowbit(std::size_t x) noexcept {
			return x & -x;
		}

	public:
		explicit FenwickTree(std::size_t _n, Type &&initValue, const Operator &opt)
			: bit(_n + 1, initValue), n{_n}, opt{opt} {}

		void Set(std::size_t pos, Type &&value) {
			for (std::size_t i = pos; i <= n; i += Lowbit(i)) {
				opt(bit[i], value);
			}
		}

		Type Get(std::size_t pos, Type result = Type{}) {
			for (std::size_t i = pos; i > 0; i -= Lowbit(i)) {
				opt(result, bit[i]);
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
using Trickster::FenwickTree;