#include <bits/stdc++.h>
using namespace std;

int main() {
	auto check = [](int tag) -> bool {

	};

	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << '\n';
}