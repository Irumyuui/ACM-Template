# Educational Codeforces Round 73 题解

## A. 2048 Game

题意：给定 $n$ 个 $2^k$ 的数字，问是否能够凑出 $2048$ 。

我们可以考虑小于等于 $2048$ 的数字，每次寻找一个与我们所需的差值相近的数字，拼凑即可。

```cpp
void Main() {
	int n;
	cin >> n;
	multiset<ll,greater<>> st;
	for (int i = 0; i < n; i ++) {
		ll x;
		cin >> x;
		st.emplace_back(x);
	}
	ll tag = 0;
	while (!st.empty() && tag < 2048) {
		auto it = st.lower_bount(2048 - tag);
		if (it == st.end()) break;
		tag += *it;
		st.erast(it);
	}
	if (tag == 2048) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}
```

## B. Knights

通过稍微模拟可以发现，类似于国际象棋的颜色即为最佳摆放方式。

```cpp
auto Main() -> void {
	int n;
	cin >> n;
	for  (int i = 0; i < n; i ++) {
		for (int j = 0; j < n; j ++) {
			cout << ((i + j) & 1 ? 'B' : 'W');
		}
		cout << '\n';
	}
}
```

## C. Perfect Team

```cpp
auto Main() -> void {
	ll a, b, c;
	cin >> a >> b >> c;
	cout << min({a, b, (a + b + c) / 3}) << '\n';
}
```

## D. Make The Fence Great Again

题意：现在有 $n$ 块木板，每块木板长度为 $a_i$ ，让其变长 $1$ 的花费为 $b_i$ 。现在要保证对于所有的木板，使得 $a_{i-1} \neq a_{i}$ ，问最小花费是多少。

我们可以枚举一下第 $i$ 块的情况。

- 若 $a_i \neq a_{i - 1}$ 时，那么我们不需要改动。
- 若 $a_i = a_{i-1}$ 时，那么我们只需要让这块木板 +1 即可。

如果有一连续的木板是一样的高度，那么其高度只会在 $0,1,2,0,1,2,\cdots$ 这样。因此，只需要考虑第 $i - 1$ 块木板和第 $i$ 块木板在 $0, 1, 2$ 增加高度下的情况即可，这个过程可以使用动态规划的方式进行解决。

```cpp
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;
void Main() {
	int n;
	cin >> n;
	vector<ll> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i] >> b[i];
	}
	a[0] = -inf<ll>;

	ll ret = 0;
	vector f(n + 1, array{inf<ll>, inf<ll>, inf<ll>});
	f[0] = {};
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= 2; j ++) {
			for (int k = 0; k <= 2; k ++) {
				if (a[i - 1] + j != a[i] + k) {
					f[i][k] = min(f[i][k], f[i - 1][j] + k * b[i]);
				}
			}
		}
	}
	cout << rgs::min(f[n]) << '\n';
}
```