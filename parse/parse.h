#pragma once
#include "graph.h"


struct sem_stack {
	sem_stack & operator=(sem_stack const&) = default;
	sem_stack(sem_stack const&) = default;
	std::stack<int> now_pos;
	std::stack<type_token> now_type;
	void push_id(int now) {
		now_pos.push(now);
		now_type.push(type_token::identifier);
	}
	void push_str(int now) {
		now_pos.push(now);
		now_type.push(type_token::string_literal);
	}
	void push_char(int now) {
		now_pos.push(now);
		now_type.push(type_token::char_literal);
	}
	void push_int(int now) {
		now_pos.push(now);
		now_type.push(type_token::int_literal);
	}
	void push_float(int now) {
		now_pos.push(now);
		now_type.push(type_token::double_literal);
	}
	type_token now() { return now_type.top(); }
	int pop_now() {
		int n = now_pos.top();
		now_pos.pop();
		
	}
	
};
enum class quad_op {
	label ,
	jmp,
	branch ,
	newvar ,
	func ,
	funcparam ,
	structdef,
	strmem,
	cblock,
	push ,
	call,
	ret,
	arrayval, structval , 
	add, sub,mul, div, mod ,
	shl, shr, 
	e, ne, ge, le, l,g,
	bxor,bor,band,lor,land, 
	incb,ince ,decb,dece, bnot, lnot, pos, neg, 
	assign,
};
namespace assign_type {
	extern const int normal, add, sub, mul, div, mod, shl, shr, and, or , xor;
}
struct parser {
	using quad_info = std::array<int, 3>;
	using quad_type = std::pair<quad_op, quad_info >;
	lex_data const& data;
	grammar & grm;
	int quad_top;
	sem_stack stack;

	std::map<int, std::pair<int, int> > quad_history;
	std::vector<quad_type> quads;
	std::stack<sem_stack> stack_quad;
	void add_quad(quad_op, int, int, int);
	void return_to(int);
	void new_history(int);
	int all_cnt;
	int action_called_cnt;
	parser(lex_data const& d, grammar &g);

};