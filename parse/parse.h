#pragma once
#include "graph.h"


struct labels {
	enum label_type {
		loop_begin,
		loop_end,
		for_suf,
		for_begin,
		if_end,
		else_end,
		user,
		switch_end,
		case_end,
		fail
	};
	labels & operator=(labels const&) = default;
	labels(labels const&) = default;
	labels() = default;
	using label = std::pair<int, label_type >;
	std::vector<label> vec_label;
	auto begin() {
		return vec_label.rbegin();
	}
	auto end() {
		return vec_label.rend();
	}
	auto begin() const{
		return vec_label.crbegin();
	}
	auto end() const{
		return vec_label.crend();
	}
	void push(label_type ty, int i) {
		vec_label.emplace_back(i, ty);
	}
	label pop() {
		auto x = vec_label.back();
		vec_label.pop_back();
		return x;
	}
	auto operator[](int i) {
		return vec_label[i];
	}
	auto top_type( ) {
		return vec_label.back().second;
	}
	label find_nearest(label_type ty) {
		for (auto it=vec_label.rbegin();it!=vec_label.rend();it++) {
			if (it->second == ty)return *it;
		}
		return label{ -1,fail };
	}
};
struct vars {
	vars & operator=(vars const&) = default;
	vars(vars const&) = default;
	vars() = default;
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
	int pop() {
		int n = now_pos.top();
		now_pos.pop();
		return n;
	}
	int top() {
		return now_pos.top();
	}
	
};
enum class quad_op {
	label ,
	jmp,
	btrue ,
	bfalse, 
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
	inc ,dec, bnot, lnot, pos, neg, 
	assign,
};
namespace assign_type {
	extern const int normal, add, sub, mul, div, mod, shl, shr, and, or , xor;
}


struct parser {
	using quad_info = std::array<int, 3>;
	using quad_type = std::pair<quad_op, quad_info >;
	lex_data data;

	grammar & grm;
	int quad_top;
	vars stack;
	labels label_stack;

	std::map<int, std::pair<int, int> > quad_history;
	std::vector<quad_type> quads;
	std::stack<vars> rec_stack_vars;
	std::stack<labels> rec_stack_labels;
	void add_quad(quad_op, int, int, int);
	void return_to(int);
	void new_history(int);
	int push_tmp_var();
	int alloc_tmp_var();
	int push_label(labels::label_type ty);
	void push_label(int i, labels::label_type ty);
	int pop_label();
	int tmp_var_cnt;
	int	label_cnt;
	int input_data_cnt;
	int action_called_cnt;
	parser(lex_data const& d, grammar &g);

};