#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
void Main();
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}

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
	template <class T> constexpr Fwrite& operator << (const T &x) {
		this->write(x);
		return *this;
	}
} fout;


#define cin fin
#define cout fout

const int N = 2e5 + 10;

struct Node {
	ll val;
	int lc, rc;
	Node(const ll &v = inf<ll>, const int l = {}, const int r = {}) : val(v), lc(l), rc(r) {}
} seg[N * 60];
int tt = 0;
// int ver[N * 30];
int getNode() {
	return ++ tt;
}
void extend(int nid, int oid) {
	seg[nid] = seg[oid];
}
void build(int l, int r, int &id) {
	id = getNode();
	if (l == r) {
		seg[id].val = inf<ll>;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, seg[id].lc);
		build(mid + 1, r, seg[id].rc);
		// rise(id);
	}
}
void change(int l, int r, int oid, int &nid, int tag, ll d) {
	nid = getNode();
	if (l == r) {
		seg[nid].val = min({seg[nid].val, d, seg[oid].val});
	} else {
		int mid = l + ((r - l) >> 1);
		extend(nid, oid);
		if (tag <= mid) {
			change(l, mid, seg[oid].lc, seg[nid].lc, tag, d);
		} else {
			change(mid + 1, r, seg[oid].rc, seg[nid].rc, tag, d);
		}
	}
}
ll query(int l, int r, int id, int tag) {
	if (id == 0) {
		return inf<ll>;
	}
	if (l == r) {
		if (l == tag) {
			return seg[id].val;
		} else {
			return inf<ll>;
		}
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			return query(l, mid, seg[id].lc, tag);
		} else {
			return query(mid + 1, r, seg[id].rc, tag);
		}
	}
}

void Main() {
	int n, m;
	cin >> n >> m;
	vector<ll> transe;
	vector<array<ll,4>> segs; // l, r, len, w
	for (int i = 0; i < n; i ++) {
		ll l, r, len, w;
		cin >> l >> r >> w;
		len = r - l + 1;
		transe.push_back(l);
		transe.push_back(r);
		segs.push_back({l, r, len, w});
	}
	sort(transe.begin(), transe.end());
	transe.erase(unique(transe.begin(), transe.end()), transe.end());
	for (auto &[l, r, len, w] : segs) {
		l = lower_bound(transe.begin(), transe.end(), l) - transe.begin() + 1;
		r = lower_bound(transe.begin(), transe.end(), r) - transe.begin() + 1;
	}
	sort(segs.begin(), segs.end(), [](const auto &a, const auto &b) {
		return a[1] < b[1];
	});
	int nn = 2e5;
	int lst{0}, nm = int(transe.size());
	vector<int> ver(nm + 10);
	ll ans = inf<ll>;
	build(1, nn, ver[0]);
	for (int i = 1; i <= nm; i ++) {
		ver[i] = ver[i - 1];
		while (lst < n) {
			auto [l, r, len, w] = segs[lst];
			if (r > i) {
				break;
			}
			auto ret = query(1, nn, ver[l - 1], m - len) + w;
			ans = min(ans, ret);
			change(1, nn, ver[i], ver[i], len, w);
			lst ++;
		}
	}
	if (ans >= inf<ll>) {
		cout << -1 << '\n';
	} else {
		cout << ans << '\n';
	}
}