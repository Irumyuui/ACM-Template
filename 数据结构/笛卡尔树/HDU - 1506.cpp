#include <bits/stdc++.h>

using i64 = std::int64_t;

void Main(int n) {
    std::vector<i64> h(n);    
    for (auto &x : h) std::cin >> x;

    std::vector<int> lc(n, -1), rc(n, -1), stk(n, -1);
    int top = -1;
    for (int i = 0; i < n; i ++) {
        if (top == -1) {
            stk[++ top] = i;
        } else {
            int k = top;
            while (k >= 0 && h[i] <= h[stk[k]]) -- k;
            if (k >= 0) rc[stk[k]] = i;
            if (k < top) lc[i] = stk[k + 1];
            stk[++ k] = i;
            top = k;            
        }
    }

    std::vector<int> siz(n);
    i64 ans = 0;
    auto dfs = [&](auto &&dfs, int from) -> int {
        siz[from] = 1;
        if (lc[from] != -1) {
            siz[from] += dfs(dfs, lc[from]);
        }
        if (rc[from] != -1) {
            siz[from] += dfs(dfs, rc[from]);
        }
        ans = std::max(ans, siz[from] * h[from]);
        return siz[from];
    };
    dfs(dfs, stk[0]);

    std::cout << ans << '\n';
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    for (int n; std::cin >> n && n > 0; ) {
        Main(n);
    }
}