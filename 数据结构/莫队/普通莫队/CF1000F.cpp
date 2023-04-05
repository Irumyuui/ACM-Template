/**
 * https://codeforces.com/problemset/problem/1000/F
*/

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>

using namespace std;

using i64 = int64_t;

struct Fread {
	char *p1, *p2, buf[100000];
	constexpr char nextchar() noexcept {
		return (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++);
	}
	template <class T> constexpr void read(T &val) noexcept {
		val = 0;
		int f = 1;
		char ch = nextchar();
		while (ch < 48 || ch > 57) {
			if (ch == '-') {
				f = -1;
			}
			ch = nextchar();
		}
		while (ch >= 48 && ch <= 57) {
			val = val * 10 + ch - 48, ch = nextchar();
		}
		val *= f;
	}
	template <class T> constexpr Fread& operator >> (T &val) noexcept {
		this->read(val);
		return *this;
	}
} fin;

struct Fwrite {
	template <class T> constexpr void write(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
	constexpr void write(char x) { putchar(x); }
	constexpr void write(const char *x) { puts(x); }
	// constexpr void write(const std::string &str) { puts(str.c_str()); }
	template <class T> constexpr Fwrite& operator << (const T &x) {
		this->write(x);
		return *this;
	}
} fout;

#define cin fin
#define cout fout

void Main() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}

	int q;
	cin >> q;
	struct Query {
		int l, r, idx;
	};
	vector<Query> que(q);
	for (int t = 0; auto &[l, r, idx] : que) {
		cin >> l >> r;
		idx = t ++;
	}
	ranges::sort(que, [block{int(sqrt(n))}](const auto &a, const auto &b) -> bool {
		if (a.l / block != b.l / block) 
			return a.l < b.l;
		if (a.l / block % 2)
			return a.r < b.r;
		return a.r > b.r;
	});

	vector<int> cnt(ranges::max(a | views::drop(1)) + 1);
	// set<int> ls;
	vector<int> stk{0}, stk_pos(cnt);
	stk.reserve(n * 2);
	auto Add = [&](int pos) {
		cnt[a[pos]] ++;
		if (cnt[a[pos]] == 1) {
			stk_pos[a[pos]] = stk.size();
			stk.emplace_back(a[pos]);
		} else if (cnt[a[pos]] == 2) {
			stk_pos[stk.back()] = stk_pos[a[pos]];
			swap(stk.back(), stk[stk_pos[a[pos]]]);
			stk.pop_back();
		}
	};
	auto Del = [&](int pos) {
		cnt[a[pos]] --;
		if (cnt[a[pos]] == 1) {
			stk_pos[a[pos]] = stk.size();
			stk.emplace_back(a[pos]);
		} else if (cnt[a[pos]] == 0) {
			stk_pos[stk.back()] = stk_pos[a[pos]];
			swap(stk.back(), stk[stk_pos[a[pos]]]);
			stk.pop_back();
		}
	};

	int L = 1, R = 0;
	vector<int> ans(q);
	for (const auto [l, r, idx] : que) {
		while (L > l)
			Add(-- L);
		while (R < r)
			Add(++ R);
		while (L < l)
			Del(L ++);
		while (R > r)
			Del(R --);
		ans[idx] = stk.back();
	}

	for (auto x : ans) {
		cout << x << '\n';
	}
}

int main() {
	// std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}