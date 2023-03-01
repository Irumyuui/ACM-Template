#include <bits/stdc++.h>

using ll = int64_t;

std::tuple<ll,ll,ll> exgcd(ll a, ll b) {
	if (b == 0) {
		return {a, 1, 0};
	} else {
		auto [d, x, y] = exgcd(b, a % b);
		return {d, y, x - a / b * y};
	}
}
ll inv(ll a, ll p) {
	auto [d, x, y] = exgcd(a, p);
	return x;
}

int main() {

}