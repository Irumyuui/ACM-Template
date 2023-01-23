#include <bits/stdc++.h>

template <typename Contained, std::size_t Side>
struct Matrix {
	auto &at(std::size_t R, std::size_t C) {
		return data[R * Side + C];
	}
	const auto &at(std::size_t R, std::size_t C) const {
		return data[R * Side + C];
	}
	Matrix operator * (const Matrix &that) const {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t k{}; k < Side; k ++) {
				const Contained &r = (*this).at(i, k);
				for (std::size_t j{}; j < Side; j ++)
					ret.at(i, j) += r * that.at(k, j);
			}
		return ret;
	}
	Matrix &operator *= (const Matrix &that) {
		*this = (*this) * that;
		return *this;
	}
	Matrix operator + (const Matrix &that) const {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t j{}; j < Side; j ++)
					ret.at(i, j) = (*this).at(i, j) + that.at(i, j);
		return ret;
	}
	Matrix &operator += (const Matrix &that) {
		for (std::size_t i{}; i < Side; i ++)
			for (std::size_t j{}; j < Side; j ++)
					(*this).at(i, j) += that.at(i, j);
		return *this;
	}
	Matrix &operator ^= (long long pow_i) {
		Matrix ret{};
		for (std::size_t i{}; i < Side; i ++)
			ret.at(i, i) = 1;
		for (; pow_i > 0; pow_i >>= 1, (*this) *= (*this)) 
			if (pow_i % 2)
				ret *= (*this);
		*this = ret;
		return *this;
	}
	Matrix operator ^ (long long pow_i) const {
		Matrix ret = *this;
		ret ^= pow_i;
		return ret;
	}
	std::array<Contained, Side * Side> data;
};