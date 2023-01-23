#include <bits/stdc++.h>

namespace numberTheory
{

template <typename Type>
inline constexpr auto abs(const Type &_value) noexcept -> Type {
    return _value < 0 ? (-_value) : _value;
}

template <typename Type>
inline constexpr auto exgcd(Type a, Type b) noexcept -> std::array<Type,3> {	
    return [&](auto &&func) constexpr noexcept -> std::array<Type, 3> {
        return func(func, abs(a), abs(b));
    }(
        [](auto &&self, Type __a, Type __b) constexpr noexcept -> std::array<Type, 3> {
            if (__b == 0) {
                return std::array<Type, 3>{__a, 1, 0};
            } else {
                auto [d, x, y] = self(self, __b, __a % __b);
                return std::array<Type, 3>{d, y, x - __a / __b * y};
            }
        }
    );
}

template <typename Type>
inline constexpr auto gcd(const Type &a, const Type &b) noexcept -> Type {
    return [&](auto &&func) noexcept -> Type {
        return func(func, abs(a), abs(b));
    } (
        [](auto &&self, Type a, Type b) noexcept -> Type {
            if (b == 0) {
                return a;
            } else {
                return self(self, b, a % b);
            }
        }
    );
}

template <typename Type>
inline constexpr auto gcd(const std::initializer_list<Type> &value_list) noexcept -> Type {
    Type ret = Type{0};
	for (const auto &v : value_list) {
		ret = gcd(ret, v);
	}
	return ret;
}

template <typename Type>
inline constexpr auto lcm(const Type &a, const Type &b) noexcept -> Type {
	if (a == 0 || b == 0) {
		return Type{0};
	}
	return a / gcd(a, b) * b;
}

template <typename Type>
inline constexpr auto lcm(const std::initializer_list<Type> &value_list) noexcept -> Type {
	Type ret = Type{1};
	for (const auto &v : value_list) {
		ret = lcm(ret, v);
		if (ret == 0) {
			return Type{0};
		}
	}
	return ret;
}

}

int main() {

}