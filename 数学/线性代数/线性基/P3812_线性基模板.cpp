#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct Linear_Base {
	std::vector<T> a;
	auto insert(T x) -> void {
		for (auto i : a) 
			x = min(x, i ^ x);
		for (auto &i : a)
			i = min(i, i ^ x);
		if (x)
			a.emplace_back(x);
	}
	auto ask() -> T {
		T ret = {};
		for (auto i : a)
			ret ^= i;
		return ret;
	}
	auto operator += (const Linear_Base &that) -> Linear_Base& {
		for (auto it : that.a) 
			insert(it);
		return *this;
	}
	auto operator + (const Linear_Base &that) const -> Linear_Base {
		auto ret = *this;
		ret += that;
		return ret;
	}
};

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n;
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; i ++) {
		cin >> a[i];
	}

	vector<ll> b;
	b.reserve(n);
	auto insert = [&](ll x) {
		for (auto i : b) 
			x = min(x, i ^ x);
		for (auto &i : b) 
			i = min(i, i ^ x);
		if (x)
			b.push_back(x);
	};
	
	for (auto it : a) {
		insert(it);
	}

	// 异或和即为
	ll ans = 0;
	for (auto it : b) {
		ans ^= it;
	}
	cout << ans << '\n';
}