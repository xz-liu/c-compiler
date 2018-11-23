#pragma once
#include "graph.h"
struct lr_item {
	int exp_s;
	int exp;
	int pos;
	lr_item(int s, int e, int p)
		:exp_s(s), exp(e), pos(p) {}
	lr_item(lr_item &&) = default;
	lr_item(lr_item const&) = default;
	bool operator<(const lr_item& rhs) {
		if (exp_s == rhs.exp_s) {
			if (exp == rhs.exp) {
				return pos < rhs.pos;
			}return exp < rhs.exp;
		}return exp_s < rhs.exp_s;
	}
};
struct lr_dfa {
	std::vector < std::set<lr_item> > states;
	std::vector<std::map<int, int>> trans;
};