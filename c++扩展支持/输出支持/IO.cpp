#include <bits/stdc++.h>

namespace RoyalGuard::IO {
	namespace Container {
		void read(std::istream &in, auto &container) {
			for (auto &value : container) in >> value;
		}
		void write(std::ostream &out, const auto &container) {
			auto it = container.begin();
			if (it == container.end()) return;
			out << *it; ++ it;
			while (it != container.end()) { out << ' ' << *it; ++ it; }
		}
	}
	
	template <typename Key, typename Value>
	std::istream& operator >> (std::istream &in, std::pair<Key,Value> &pair) {
		in >> pair.first >> pair.second;
		return in;
	}
	template <typename Key, typename Value>
	std::ostream& operator << (std::ostream &out, const std::pair<Key,Value> &pair) {
		out << pair.first << ' ' << pair.second;
		return out;
	}

	template <typename Type, std::size_t N>
	std::istream& operator >> (std::istream &in, std::array<Type, N> &arr) {
		Container::read(in, arr);
		return in;
	}
	template <typename Type, std::size_t N>
	std::ostream& operator << (std::ostream &out, const std::array<Type, N> &arr) {
		Container::write(out, arr);
		return out;
	}

	template <typename Type>
	std::istream& operator >> (std::istream &in, std::vector<Type> &vec) {
		Container::read(in, vec);
		return in;
	}
	template <typename Type>
	std::ostream& operator << (std::ostream &out, const std::vector<Type> &vec) {
		Container::write(out, vec);
		return out;
	}
}