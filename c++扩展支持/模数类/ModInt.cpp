#include <bits/stdc++.h>

namespace RoyalGuard::Integer {
	template <int _P>
	struct ModInt32 {
		using i64 = std::int64_t;
		static constexpr int P = _P;
		int v;
		ModInt32() : v(0) {}
		ModInt32(i64 _v) { v = _v % P; if (v < 0)v += P; }
		explicit operator int() const { return v; }
		explicit operator long long() const { return v; }
		explicit operator bool() const { return v > 0; }
		bool operator == (const ModInt32 &o) const { return v == o.v; }
		bool operator != (const ModInt32 &o) const { return v != o.v; }
		ModInt32 operator - () const { return ModInt32(v ? P - v : 0); }
		ModInt32 operator + () const { return *this; }
		ModInt32 & operator ++ () { v++; if (v == P)v = 0; return *this; }
		ModInt32 & operator -- () { if (v == 0)v = P; v--; return *this; }
		ModInt32 operator ++ (int) { ModInt32 r = *this; ++*this; return r; }
		ModInt32 operator -- (int) { ModInt32 r = *this; --*this; return r; }
		ModInt32 & operator += (const ModInt32 &o) { v += o.v; if (v >= P)v -= P; return *this; }
		ModInt32 operator + (const ModInt32 & o)const { return ModInt32(*this) += o; }
		ModInt32 & operator -= (const ModInt32 & o) { v -= o.v; if (v < 0)v += P; return *this; }
		ModInt32 operator - (const ModInt32 &o)const { return ModInt32(*this) -= o; }
		ModInt32 & operator *=(const ModInt32 & o) { v = (int)(((i64)v)*o.v%P); return *this; }
		ModInt32 operator * (const ModInt32 & o)const { return ModInt32(*this) *= o; }
		ModInt32 & operator /= (const ModInt32 & o) { return (*this) *= o.Inv(); }
		ModInt32 operator / (const ModInt32 & o)const { return ModInt32(*this) /= o; }
		friend ModInt32 operator + (const ModInt32 &x, const i64 &o) { return x + (ModInt32)o; }
		friend ModInt32 operator + (const i64 &o, const ModInt32 &x) { return x + (ModInt32)o; }
		friend ModInt32 operator - (const ModInt32 &x, const i64 &o) { return x - (ModInt32)o; }
		friend ModInt32 operator - (const i64 &o, const ModInt32 &x) { return (ModInt32)o - x; }
		friend ModInt32 operator * (const ModInt32 &x, const i64 &o) { return x * (ModInt32)o; }
		friend ModInt32 operator * (const i64 &o, const ModInt32 &x) { return x * (ModInt32)o; }
		friend ModInt32 operator / (const ModInt32 &x, const i64 &o) { ModInt32 c = o; return x * c.Inv(); }
		friend ModInt32 operator / (const i64 &o, const ModInt32 &x) { ModInt32 c = o; return c * x.Inv(); }
		ModInt32 operator ^ (i64 o)const { ModInt32 r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
		ModInt32 operator ~ () { return (*this) ^ (P - 2); }
		ModInt32 Inv() const { return (*this) ^ (P - 2); }
		friend std::istream & operator >> (std::istream &in, ModInt32 &x) { i64 d; in >> d; x = d; return in; }
		friend std::ostream & operator << (std::ostream &out, const ModInt32 &x) { out << x.v; return out; }
	};

	template <std::int64_t _P>
	struct Modint64_t {
		using i128 = __int128_t;
		static constexpr int64_t P = _P;
		int64_t v;
		Modint64_t() : v(0) {}
		Modint64_t(const i128 &_v) { v = _v % P; if (v < 0) v += P; }
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
		Modint64_t& operator *= (const Modint64_t &o) { v = (int64_t)(((i128)v)*o.v%P); return *this; }
		Modint64_t operator * (const Modint64_t &o) const { return Modint64_t(*this) *= o; }
		Modint64_t& operator /= (const Modint64_t &o) { return (*this) *= o.Inv(); }
		Modint64_t operator / (const Modint64_t &o) const { return Modint64_t(*this) /= o; }
		friend Modint64_t operator + (const Modint64_t &x, const i128 &o) { return x + (Modint64_t)o; }
		friend Modint64_t operator + (const i128 &o, const Modint64_t &x) { return x + (Modint64_t)o; }
		friend Modint64_t operator - (const Modint64_t &x, const i128 &o) { return x - (Modint64_t)o; }
		friend Modint64_t operator - (const i128 &o, const Modint64_t &x) { return (Modint64_t)o - x; }
		friend Modint64_t operator * (const Modint64_t &x, const i128 &o) { return x * (Modint64_t)o; }
		friend Modint64_t operator * (const i128 &o, const Modint64_t &x) { return x * (Modint64_t)o; }
		friend Modint64_t operator / (const Modint64_t &x, const i128 &o) { Modint64_t c = o; return x * c.Inv(); }
		friend Modint64_t operator / (const i128 &o, const Modint64_t &x) { Modint64_t c = o; return c * x.Inv(); }
		Modint64_t operator ^ (i128 o)const { Modint64_t r = 1, t = v; while (o) { if (o & 1)r *= t; t *= t; o >>= 1; }return r; }
		Modint64_t operator ~ () { return (*this) ^ (P - 2); }
		Modint64_t Inv() const { return (*this) ^ (P - 2); }
		friend std::istream & operator >> (std::istream &in, Modint64_t &x) { int64_t d; in >> d; x = d; return in; }
		friend std::ostream & operator << (std::ostream &out, const Modint64_t &x) { out << x.v; return out; }
	};
}
using mint = RoyalGuard::Integer::ModInt32<int(1e9 + 7)>;