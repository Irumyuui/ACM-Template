#include <bits/stdc++.h>

namespace Trickster {
	template <typename _Tp>
	class FenwickTree {
	public:
		using Type = _Tp;

	private:
		constexpr static std::size_t Lowbit(std::size_t x) noexcept {
			return x & -x;
		}

	public:
		explicit FenwickTree(std::size_t _n, Type &&initValue = {}) : bit(_n + 1, initValue), n{_n} {}

		template <typename Operator>
		void Update(std::size_t pos, Type &&value, const Operator &opt) {
			for (std::size_t i = pos; i <= n; i += Lowbit(i)) {
				opt(bit[i], value);
			}
		}

		template <typename Operator>
		Type Ask(std::size_t pos, Type result, const Operator &opt) {
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
	};
}
using Trickster::FenwickTree;