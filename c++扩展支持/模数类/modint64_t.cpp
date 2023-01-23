#include <bits/stdc++.h>

template <int64_t _P>
struct Modint64_t {
	using int128_t = __int128_t;
	static constexpr int64_t P = _P;
	int64_t v;
	Modint64_t() : v(0) {}
	Modint64_t(const int128_t &_v) { v = _v % P; if (v < 0) v += P; }
	explicit operator long long() const { return v; }
	explicit operator bool() const { return v > 0; }
	bool operator == (const Modint64_t &o) const { return v == o.v; }
	bool operator != (const Modint64_t &o) const { return v != o.v; }
	Modint64_t operator - () const { return Modint64_t(v ? P - v : 0); }
	Modint64_t operator + () const { return *this; }
	Modint64_t& operator ++ () { ++ v; if (v == P) v = 0; return *this; }
	Modint64_t& operator -- () { if (v == 0) v = P; -- v; return *this; }
	Modint64_t operator ++ (int) { Modint64_t r = *this; ++ *this; return r; }
	Modint64_t operator -- (int) { Modint64_t r = *this; -- *this; return r; }
	Modint64_t& operator += (const Modint64_t &o) { v += o.v; if (v >= P) v -= P; return *this;}
	Modint64_t operator + (const Modint64_t &o) const { return Modint64_t(*this) += o; }
	Modint64_t& operator -= (const Modint64_t &o) { v -= o.v; if (v < 0) v += P; return *this; }
	Modint64_t operator - (const Modint64_t &o) const { return Modint64_t(*this) -= o; }
	Modint64_t& operator *= (const Modint64_t &o) { v = (int64_t)(((int128_t)v)*o.v%P); return *this; }
	Modint64_t operator * (const Modint64_t &o) const { return Modint64_t(*this) *= o; }
	Modint64_t& operator /= (const Modint64_t &o) { return (*this) *= o.Inv(); }
	Modint64_t operator / (const Modint64_t &o) const { return Modint64_t(*this) /= o; }
	friend Modint64_t operator + (const Modint64_t &x, const int128_t &o) { return x + (Modint64_t)o; }
	friend Modint64_t operator + (const int128_t &o, const Modint64_t &x) { return x + (Modint64_t)o; }
	friend Modint64_t operator - (const Modint64_t &x, const int128_t &o) { return x - (Modint64_t)o; }
	friend Modint64_t operator - (const int128_t &o, const Modint64_t &x) { return (Modint64_t)o - x; }
	friend Modint64_t operator * (const Modint64_t &x, const int128_t &o) { return x * (Modint64_t)o; }
	friend Modint64_t operator * (const int128_t &o, const Modint64_t &x) { return x * (Modint64_t)o; }
	friend Modint64_t operator / (const Modint64_t &x, const int128_t &o) { Modint64_t c = o; return x * c.Inv(); }
	friend Modint64_t operator / (const int128_t &o, const Modint64_t &x) { Modint64_t c = o; return c * x.Inv(); }
	Modint64_t operator ^ (int128_t o)const { Modint64_t r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
	Modint64_t operator ~ () { return (*this) ^ (P - 2); }
	Modint64_t Inv() const { return (*this) ^ (P - 2); }
	friend std::istream & operator >> (std::istream &in, Modint64_t &x) { int64_t d; in >> d; x = d; return in; }
	friend std::ostream & operator << (std::ostream &out, const Modint64_t &x) { out << x.v; return out; }
};

