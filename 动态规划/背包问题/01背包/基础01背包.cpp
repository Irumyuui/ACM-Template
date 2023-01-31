#include <bits/stdc++.h>
using namespace std;
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

// 二维状态数组
void solve1() {
	int n, m;
	cin >> n >> m;
	vector<int> v(n + 1), w(n + 1);
	for (int i = 1; i <= n; i ++)
		cin >> v[i] >> w[i];
	vector f(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; i ++) 
		for (int j = 0; j <= m; j ++) 
			if (j >= v[i])
				f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
			else
				f[i][j] = f[i - 1][j];
}

// 节省内存
// 最好少用
void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> f(m + 1, -inf<int>);
	f[0] = 0;
	for (int i = 0; i < n; i ++) {
		int v, w;
		cin >> v >> w;
		for (int j = m; j >= v; j --) 
			f[j] = max(f[j], f[j - v] + w);
	}
}

int main() {

}