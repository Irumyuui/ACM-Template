#include <bits/stdc++.h>

const int N = 1e5 + 10;
int lg[N];
void init() {
	lg[0] = lg[1] = 0;
	for (int i = 2; i < N; i ++) {
		lg[i] = lg[i / 2] + 1;
	}
}