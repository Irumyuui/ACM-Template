#include <bits/stdc++.h>

struct Splitmix64Hash {
    const std::size_t randomNumber;
    
    constexpr Splitmix64Hash() noexcept : randomNumber{GetTimeStep()} {}
    
    constexpr static auto GetTimeStep() noexcept -> std::size_t {
        constexpr auto &tim = __TIME__;
        return Splitmix64(std::size_t{(tim[0] - '0') * 10 + (tim[1] - '0')} * 3600
                    + std::size_t{(tim[3] - '0') * 10 + (tim[4] - '0')} * 60
                    + std::size_t{(tim[5] - '0') * 10 + (tim[6] - '0')});
    }
    
    constexpr static auto Splitmix64(std::size_t x) noexcept -> std::size_t {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    template <std::integral T>
    constexpr auto operator () (const T &x) const noexcept -> std::size_t {
        return Splitmix64(static_cast<std::size_t>(x) + randomNumber);
    }

    template <std::integral T1, std::integral T2>
    constexpr auto operator () (const std::pair<T1,T2> &x) const noexcept -> std::size_t {
        return Splitmix64((static_cast<std::size_t>(x.first) + randomNumber)
                        ^ (static_cast<std::size_t>(x.second) + randomNumber));
    }
};

template <typename Key, typename Value, typename Hash = Splitmix64Hash>
using HashMap = std::unordered_map<Key, Value, Hash>;
template <typename Type, typename Hash = Splitmix64Hash>
using HashSet = std::unordered_set<Type, Hash>;