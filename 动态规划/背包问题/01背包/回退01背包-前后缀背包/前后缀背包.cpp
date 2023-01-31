#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	vector<int> v(n + 1), w(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> v[i] >> w[i];
	}

	vector f(n + 2, vector<int>(m + 1)), g(f);
	// 前缀背包
	for (int i = 1; i <= n; i ++) 
		for (int j = 0; j <= m; j ++) 
			if (j >= v[i]) 
				f[i][j] = max(f[i - 1][j], f[i - 1][j - v[i]] + w[i]);
			else
				f[i][j] = f[i - 1][j];
	// 后缀背包
	for (int i = n; i >= 1; i --) 
		for (int j = 0; j <= m; j ++)
			if (j >= v[i]) 
				g[i][j] = max(g[i + 1][j], g[i + 1][j - v[i]] + w[i]);
			else
				g[i][j] = g[i - 1][j];

	for (int i = 1; i <= n; i ++) {
		int ret1 = 0, ret2 = 0;
		// 去掉第i个物品
		for (int j = 0; j <= m; j ++)
			ret1 = max(ret1, f[i - 1][j] + g[i + 1][m - j]);	
		// 添加第i个物品
		for (int j = 0; j <= m - v[i]; j ++)
			ret2 = max(ret2, f[i - 1][j] + g[i + 1][m - v[i] + j] + w[i]);
	}
}