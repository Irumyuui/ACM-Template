#pragma once

#include <bits/stdc++.h>

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#define THIS_WITH_FMT_HEADER_ONLY
#endif

// #include <fmt/core.h>
// #include <fmt/format.h>
// #include <fmt/ranges.h>

#include "fmt-lib/core.h"
#include "fmt-lib/format.h"
#include "fmt-lib/ranges.h"

namespace FmtDebugLib::PrintFormat {
	template <typename Type>
	std::string ToString(Type value) {
		auto ret = fmt::format("{0}", value);
		return ret;
	}

	template <typename Type, typename Container>
	std::string ToString(std::stack<Type, Container> stk) {
		std::string ret = "[";
		if (stk.empty()) {
			return ret;
		}
		std::vector<Type> seq;
		while (!stk.empty()) {
			seq.emplace_back(stk.top());
			stk.pop();
		}
		std::reverse(seq.begin(), seq.end());
		for (int i = 0; i + 1 < seq.size(); i ++) {
			ret += fmt::format("{0}, ", seq[i]);
		}
		ret += fmt::format("{0}", seq.back());
		return ret;
	}

	template <typename Type, typename Container>
	std::string ToString(std::queue<Type, Container> que) {
		std::string ret = "<";
		if (que.empty()) {
			return ret + "<";
		}
		while (!que.empty()) {
			auto value = que.front();
			que.pop();
			if (que.empty()) {
				ret += fmt::format("{0}", value);
			} else {
				ret += fmt::format("{0}, ", value);
			}
		}
		return ret + "<";
	}

	template <typename Type, typename Container, typename Compare>
	std::string ToString(std::priority_queue<Type, Container, Compare> pq) {
		std::string ret = "Top <= ";
		while (!pq.empty()) {
			auto value = pq.top();
			pq.pop();
			if (pq.empty()) {
				ret += fmt::format("{0}", value);
			} else {
				ret += fmt::format("{0}, ", value);
			}
		}
		return ret;
	}

	template <std::size_t N>
	std::string ToString(std::bitset<N> bit) {
		std::string ret;
		for (int i = int(N) - 1; i >= 0; i --) {
			if (bit[i]) {
				ret += '1';
			} else {
				ret += '0';
			}
		}
		return ret;
	}
}

namespace FmtDebugLib {

	template <typename Type>
	inline constexpr void DebugPrint(const char *name, const Type &tag) {
		// fmt::print(stderr, "{0}={1}\n", name, PrintFormat::ToString(tag));
		std::cerr << name << '=' << PrintFormat::ToString(tag) << std::endl;
	}
	
	template <typename Type, typename... TypeArgs>
	inline constexpr void DebugPrint(const char *name, const Type &beginArgs, const TypeArgs &...argsList) {
		while (*name != ',') {
			// fmt::print(stderr, "{}", *name ++);
			std::cerr << *name ++ << std::flush;
		}
		// fmt::print(stderr, "={},", PrintFormat::ToString(beginArgs));
		// std::cerr << "=" << PrintFormat::ToString(beginArgs) << ',' << std::flush;
		std::cerr << fmt::format("={},", PrintFormat::ToString(beginArgs)) << std::flush;
		DebugPrint(name + 1, argsList...);
	}

	template <typename... Args>
	inline constexpr void Debug(int codeLine, const char *name, const Args &...args) {
		// fmt::print(stderr, "[{0}] ", codeLine);
		// std::cerr << "[" << codeLine << "] " << std::flush;
		std::cerr << fmt::format("[{0}] ", codeLine) << std::flush;
		DebugPrint(name, args...);
	}
}

#define debug(...) FmtDebugLib::Debug(__LINE__, #__VA_ARGS__, __VA_ARGS__)

#ifdef THIS_WITH_FMT_HEADER_ONLY
#undef THIS_WITH_FMT_HEADER_ONLY
#undef FMT_HEADER_ONLY
#endif