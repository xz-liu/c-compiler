#pragma once
#include "graph.h"

struct quad {
	int op[3];
	token op_type;
};


struct sem_stack {
	std::stack<std::string	> const_str;
	std::stack<std::int64_t> const_int;
	std::stack<double	> const_float;
	std::stack<char		> const_char;
	std::stack<std::string	> id_stack;
	std::stack<type_token> now_type;
	void push_id(std::string const& now) {
		id_stack.push(now);
		now_type.push(type_token::identifier);
	}
	void push_str(std::string const& now) {
		const_str.push(now);
		now_type.push(type_token::string_literal);
	}
	void push_char(char now) {
		const_char.push(now);
		now_type.push(type_token::char_literal);
	}
	void push_int(std::int64_t const& now) {
		const_int.push(now);
		now_type.push(type_token::int_literal);
	}
	void push_float(double now) {
		const_float.push(now);
		now_type.push(type_token::double_literal);
	}
	type_token now() { return now_type.top(); }
};




struct parser {
	lex_data const& data;
	grammar & grm;
	int now;
	sem_stack stack;
	std::map<int, std::pair<int, int> > quad_history;
	int all_cnt;
	parser(lex_data const& d, grammar &g);
	bool operator()(grammar const& grm){
		now = 0;
		return parse(grm,grm.id_s);
	}
	bool parse(grammar const& grm, int pro_s);

};