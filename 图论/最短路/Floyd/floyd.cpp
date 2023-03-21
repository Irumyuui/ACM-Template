#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;

int f[N][N];
int n;

void floyd() {
	// 按 1 到 n 的顺序 枚举加入的点
	// 也可以按其他顺序
	for (int k = 1; k <= n; k ++)
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}