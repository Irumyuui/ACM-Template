#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(0);

	int n, k;
	while (cin >> n >> k && (n || k)) {
		vector<int> a(n), b(n);
		for (auto &x : a) {
			cin >> x;
		}
		for (auto x : b) {
			cin >> x;
		}

		auto check = [&](double x) {
			vector<double> tmp(n);
			for (int i = 0; i < n; i ++) {
				tmp[i] = a[i] - b[i] * x;
			}
			sort(tmp.begin(), tmp.end(), greater());
			double ret = 0;
			for (int i = 0; i < n - k; i ++) {
				ret += tmp[i];
			}
			return ret > 0;
		};

		double l = 0, r = inf<int>, tag = 0;
		while (r - l >= 1e-5) {
			auto mid = l + ((r - l) / 2);
			if (check(mid)) {
				tag = mid;
				l = mid;
			} else {
				r = mid;
			}
		}
		cout << tag;
	}
}