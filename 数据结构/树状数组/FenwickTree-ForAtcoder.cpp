#include <bits/stdc++.h>

namespace RoyalGuard::DataStructure {
	template <typename Type, typename Operator = std::plus<Type>>
	class FenwickTree {
		public:
			FenwickTree(int size, Type initValue = Type{}, Operator opt = Operator{}) 
				: bit(size + 1, initValue), opt(opt) {}

			void Assign(int size, Type value) {
				bit.Assign(size, value);
			}

			void Update(int idx, Type dx) {
				for (int i = idx + 1; i < (int)bit.size(); i += Lowbit(i)) {
					bit[i] = opt(bit[i], dx);
				}
			}

			void Fill(Type value) {
				std::fill(bit.begin(), bit.end(), value);
			}

			Type Get(int idx, Type result = {}) const {
				for (int i = idx + 1; i > 0; i -= Lowbit(i)) {
					result = opt(result, bit[i]);
				}
				return result;
			}

		private:
			constexpr static int Lowbit(int x) noexcept {
				return x & -x;
			}

			std::vector<Type> bit;
			Operator opt;
	};
}