#include <bits/stdc++.h>
using namespace std;
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

// 没有优化
// 要搞滚动数组也行 缺点会丢失信息
void solve1() {
	int n, m;
	cin >> n >> m;
	
	vector<int> v(n + 1), w(n + 1), cnt(n + 1);
	for (int i = 1; i <= n; i ++)
		cin >> v[i] >> w[i] >> cnt[i];
	
	vector f(n + 1, vector<int>(m + 1, -inf<int>));
	// 初始化
	for (int i = 0; i <= m; i ++) 
		f[0][i] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= m; j ++) {
			for (int k = 0; k <= cnt[i]; k ++) {
				if (j >= k * v[i]) {
					f[i][j] = max({f[i - 1][j], f[i][j], f[i - 1][j - v[i] * k] + w[i] * k});  // 都不选、保留之前选的、选择现在选的
				} else {
					f[i][j] = max({f[i - 1][j], f[i][j]});  // 都不选、保留之前选的
				}
			}
		}
	}
	cout << f[n][m] << '\n';
}

// 滚动数组
void solve2() {
	int n, m;
	cin >> n >> m;
	
	vector<int> v(n + 1), w(n + 1), cnt(n + 1);
	for (int i = 1; i <= n; i ++)
		cin >> v[i] >> w[i] >> cnt[i];
	
	vector<int> f(m + 1, 0);
	for (int i = 1; i <= n; i ++)
		for (int j = m; j >= 0; j --)
			for (int k = 0; k <= cnt[i]; k ++) {
				if (j - k * v[i] >= 0) 
					f[j] = max(f[j], f[j - v[i] * k] + w[i] * k);
			}

	cout << f[m] << '\n';
}

int main() {

}