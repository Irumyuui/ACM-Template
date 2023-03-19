#include <bits/stdc++.h>

namespace __B_HASH {
	template <typename T>
#if __cplusplus >= 202002L
		requires std::is_integral_v<T>
#endif
	struct Splitmix64_Hash {
		constexpr static auto splitmix64(uint64_t x) noexcept -> uint64_t {
			x += 0x9e3779b97f4a7c15;
			x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
			x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
			return x ^ (x >> 31);
		}
		auto operator() (T x) const noexcept -> std::size_t {
			const static uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
			return splitmix64(static_cast<uint64_t>(x) + FIXED_RANDOM);
		}
	};
}
template <typename Key, typename Value, typename __Hs = __B_HASH::Splitmix64_Hash<Key>>
#if __cplusplus >= 202002L
	requires std::is_integral_v<Key>
#endif
using Hash_Map = std::unordered_map<Key, Value, __Hs>;
template <typename Value, typename __Hs = __B_HASH::Splitmix64_Hash<Value>>
#if __cplusplus >= 202002L
	requires std::is_integral_v<Value>
#endif
using Hash_Set = std::unordered_set<Value, __Hs>;	