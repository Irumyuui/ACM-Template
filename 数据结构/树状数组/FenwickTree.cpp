#include <bits/stdc++.h>

namespace RoyalGuard::DataStructure {

#if __cplusplus >= 202002L
	template <
		typename Type,
		std::regular_invocable<Type,Type> Operator = std::plus<Type>
	>
#else
	template <
		typename Type,
		typename Operator = std::plus<Type>,
		typename = std::enable_if<std::is_invocable<Operator,Type,Type>::value>::type
	>
#endif
	class FenwickTree {
	public:
		explicit FenwickTree(int size, Type initValue = Type{}, Operator opt = Operator{}) 
			: bit(size + 1, initValue), opt(opt) {}

		auto Assign(int size, Type value) -> void {
			assert(size >= 0);
			bit.Assign(size, value);
		}

		auto Update(int idx, Type dx) -> void {
			for (int i = idx + 1; i < (int)bit.size(); i += Lowbit(i)) {
				bit[i] = opt(bit[i], dx);
			}
		}

		auto Fill(Type value) -> void {
			std::fill(bit.begin(), bit.end(), value);
		}

		auto Get(int idx, Type result = {}) const -> Type {
			for (int i = idx + 1; i > 0; i -= Lowbit(i)) {
				result = opt(result, bit[i]);
			}
			return result;
		}

	private:
		constexpr static
		auto Lowbit(int x) noexcept -> int {
			return x & -x;
		}

		std::vector<Type> bit;
		Operator opt;
	};

}
