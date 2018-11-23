#pragma once
#include "graph.h"

struct quad {
	int op[3];
	token op_type;
};

struct parser {
	lex_data const& data;
	int now;
	ast result;
	parser(lex_data const& d):data(d){}
	bool operator()(grammar const& grm){
		now = 0;
		return parse(grm,grm.id_s);
	}
	bool parse(grammar const& grm, int pro_s);

};