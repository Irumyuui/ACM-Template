#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	int n;
	cin >> n;

	vector f(n + 1, vector<bool>(n + 1));
	for (int k = 1; k <= n; k ++) {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				f[i][j] = f[i][k] | f[k][j];
			}
		}
	}
}