#pragma once
#ifndef COMPILER_BASIC_H
#define COMPILER_BASIC_H

#include<cinttypes>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<any>
#include<vector>
#include<list>
#include<array>
#include<deque>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<forward_list>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include<functional>
#include<string>
#include<numeric>
#include<regex>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<iterator>
#include<thread>
#include<sstream>

template<class Seq,class Func>
void output_list(const Seq &list,Func && func) {
	std::cout << "Size:" << list.size() << " Pos:" << (&list) << std::endl;
	for (const auto &x : list) {
		auto &&y = func(x);
		std::cout << y << " ";
	}
	std::cout << std::endl;
}
template<class Seq>
void output_list(const Seq &list) {
	std::cout << "Size:" << list.size() << " Pos:" << (&list) << std::endl;
	for (const auto &x : list) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}


using uint = unsigned int;
using ulong = unsigned long long;

#define var auto

#ifdef _MSC_VER
//Visual Studio

#include <intrin.h>
#pragma intrinsic(_BitScanReverse)

uint __inline __builtin_clz(uint value) {
	unsigned long leading_zero = 0;
	if (_BitScanReverse(&leading_zero, value))
		return 31 - leading_zero;
	return 32;
}

#ifdef _WIN64
ulong __inline __builtin_clz(ulong value) {
	unsigned long leading_zero = 0;
	if (_BitScanReverse64(&leading_zero, value))
		return 63 - leading_zero;
	return 64;
}
#endif // _WIN64

#endif // _MSC_VER

struct binary_io {
	template<class Out, class Struct>
	static void write_obj(Out &out, Struct u) {
		out.write(reinterpret_cast<typename Out::char_type *>(&u), sizeof(u));
	}

	template<class Struct, class In>
	static In &read_obj(In &in, Struct &u) {
		in.read(reinterpret_cast<typename In::char_type *>(&u), sizeof(u));
		return in;
	}

	template<class Struct, class In>
	static Struct read_obj(In &in) {
		Struct u;
		in.read(reinterpret_cast<typename In::char_type *>(&u), sizeof(u));
		return u;
	}
};

template<class T>
bool set_contains(std::set<T> const& s,T const& v) {
	return s.find(v) != s.end();
}

#endif 
