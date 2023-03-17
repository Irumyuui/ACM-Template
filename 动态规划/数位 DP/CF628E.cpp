#include <bits/stdc++.h>
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

template <int _P>
struct Modint {
	using ll = int64_t;
	static constexpr int P = _P;
	int v;
	constexpr Modint() : v(0) {}
	constexpr Modint(ll _v) { v = _v % P; if (v < 0)v += P; }
	explicit constexpr operator int() const { return v; }
	explicit constexpr operator long long() const { return v; }
	explicit constexpr operator bool() const { return v > 0; }
	constexpr bool operator == (const Modint &o) const { return v == o.v; }
	constexpr bool operator != (const Modint &o) const { return v != o.v; }
	constexpr Modint operator - () const { return Modint(v ? P - v : 0); }
	constexpr Modint operator + () const { return *this; }
	constexpr Modint & operator ++ () { v++; if (v == P)v = 0; return *this; }
	constexpr Modint & operator -- () { if (v == 0)v = P; v--; return *this; }
	constexpr Modint operator ++ (int) { Modint r = *this; ++*this; return r; }
	constexpr Modint operator -- (int) { Modint r = *this; --*this; return r; }
	constexpr Modint & operator += (const Modint &o) { v += o.v; if (v >= P)v -= P; return *this; }
	constexpr Modint operator + (const Modint & o)const { return Modint(*this) += o; }
	constexpr Modint & operator -= (const Modint & o) { v -= o.v; if (v < 0)v += P; return *this; }
	constexpr Modint operator - (const Modint &o)const { return Modint(*this) -= o; }
	constexpr Modint & operator *=(const Modint & o) { v = (int)(((ll)v)*o.v%P); return *this; }
	constexpr Modint operator * (const Modint & o)const { return Modint(*this) *= o; }
	constexpr Modint & operator /= (const Modint & o) { return (*this) *= o.Inv(); }
	constexpr Modint operator / (const Modint & o)const { return Modint(*this) /= o; }
	friend constexpr Modint operator + (const Modint &x, const ll &o) { return x + (Modint)o; }
	friend constexpr Modint operator + (const ll &o, const Modint &x) { return x + (Modint)o; }
	friend constexpr Modint operator - (const Modint &x, const ll &o) { return x - (Modint)o; }
	friend constexpr Modint operator - (const ll &o, const Modint &x) { return (Modint)o - x; }
	friend constexpr Modint operator * (const Modint &x, const ll &o) { return x * (Modint)o; }
	friend constexpr Modint operator * (const ll &o, const Modint &x) { return x * (Modint)o; }
	friend constexpr Modint operator / (const Modint &x, const ll &o) { Modint c = o; return x * c.Inv(); }
	friend constexpr Modint operator / (const ll &o, const Modint &x) { Modint c = o; return c * x.Inv(); }
	constexpr Modint operator ^ (ll o)const { Modint r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
	constexpr Modint operator ~ () { return (*this) ^ (P - 2); }
	constexpr Modint Inv() const { return (*this) ^ (P - 2); }
	friend constexpr std::istream & operator >> (std::istream &in, Modint &x) { ll d; in >> d; x = d; return in; }
	friend constexpr std::ostream & operator << (std::ostream &out, const Modint &x) { out << x.v; return out; }
};
using mint = Modint<int(1e9 + 7)>;

auto Solve() -> void {
	int m, d;
	string l, r;
	cin >> m >> d >> l >> r;
	int n = l.size();

	vector f(n, vector(2, vector(m, pair{mint{0}, false})));
	// 位置 奇数1偶数0 %m剩下多少
	auto dfs = [&](auto &&dfs, auto &&digit, int pos, int wic, int les, bool lead, bool limit) -> mint {
		if (pos == n) {
			return les == 0;
		} else if (!lead && !limit && f[pos][wic][les].second) {
			return f[pos][wic][les].first;
		}
		
		int LIM = limit ? (digit[pos] - '0') : 9;
		mint ret = 0;
		if (wic == 0) {
			if (d <= LIM)
				ret = dfs(dfs, digit, pos + 1, (lead && d == 0) ? 1 : (wic ^ 1), (les * 10 + d) % m, lead && d == 0, limit && d == LIM);
		} else {
			for (int i = 0; i <= LIM; i ++) {
				if (i != d) {
					ret += dfs(dfs, digit, pos + 1, (lead && i == 0) ? 1 : (wic ^ 1), (les * 10 + i) % m, lead && i == 0, limit && i == LIM);
				}
			}
		}

		if (!lead && !limit) {
			f[pos][wic][les] = { ret, true };
		}
		return ret;
	};

	auto check = [&]() -> mint {
		for (int i = 1; i < n; i += 2) {
			if (l[i] - '0' != d) {
				return false;
			}
		}
		for (int i = 0; i < n; i += 2) {
			if (l[i] - '0' == d) {
				return false;
			}
		}
		int ret = 0;
		for (int i = 0; i < n; i ++) {
			ret = (ret * 10 + l[i] - '0') % m;
		}
		return ret == 0;
	};

	if (l == r) {
		cout << check() << '\n';
	} else {
		cout << dfs(dfs, r, 0, 1, 0, true, true) - dfs(dfs, l, 0, 1, 0, true, true) + check() << '\n';
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		Solve();
	}
}