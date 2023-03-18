#include <bits/stdc++.h>
using namespace std;

template<class T, class Fun = function<T(const T &, const T &)>>
struct SegTree {
    Fun f;
    vector<T> t;
    int n;

    SegTree(int sz, const Fun &g, T default_value = T()) : f(g) {
        n = 1;
        while (n < sz) n <<= 1;
        t.resize(n * 2, default_value);
    }

    SegTree(vector<T> &a, const Fun &g, T default_value = T()) : SegTree(a.size(), g, default_value) {
        for (int i = 0; i < n; ++i) t[i + n] = a[i];
        for (int i = n - 1; i >= 1; --i) t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void upd(int i, T x) {
        i += n;
        t[i] = f(t[i], x);
        for (i >>= 1; i > 1; i >>= 1) t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    T get(int l, int r) {
        T resL = t[0], resR = t[0];
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = f(resL, t[l++]);
            if (r & 1) resR = f(t[--r], resR);
        }
        return f(resL, resR);
    }
};

template <typename Info> 
	requires requires(Info a, Info b) { {a + b} -> std::convertible_to<Info>; }
struct ZKW_SegTree {
	std::vector<Info> seg;
	int n;

	explicit ZKW_SegTree(int _size, const Info &_default_val) : {
		n = 1;
		while (n < _size) {
			n <<= 1;
		}
		seg.assign(n * 2, _default_val);
	}
	
	template <typename Container>
		requires requires(Container con) { {con[i]} -> std::convertible_to<Info>; }
	explicit ZKW_SegTree(const Container &a, int l, int r, int _n, const Info &_default_val) : ZKW_SegTree(_n, _default_val) {
		
	}
		

	void build() {
		for (int i = n - 1; i >= 1; i --) {
			t[i] = f(t[i * 2], t[i * 2 + 1]);
		}
	}
};
