#pragma once
#include "graph.h"

struct var_scope {
	std::vector<int> id_set;
	using handle_scope = std::shared_ptr<var_scope>;
	std::vector<handle_scope> inner;
	std::shared_ptr<var_scope> father;
	var_scope(handle_scope hs): father(hs){}
};

struct types {
	using type = std::pair<int, int>;
	static const int
		none = -1,
		void_type = 0,
		int16 = 1,
		int32 = 2,
		int64 = 3,
		uint16 = 4,
		uint32 = 5,
		uint64 = 6,
		char8 = 7,
		uchar8 = 8,
		float32 = 9,
		float64 = 10,
		type_struct = 11;
	enum id_type {
		func,
		struct_type,
		variable,
		param,
	};
	using id_full_type = std::pair<id_type, type>;
	int struct_cnt;
	static int struct_id(int now) {
		return type_struct + now;
	}
};
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
	std::stack<int> now_pos;
	std::stack<type_token> now_type;
	vars & operator=(vars const&rhs) {
		now_pos = rhs.now_pos;
		now_type = rhs.now_type;
		return *this;
	}
	vars(vars const& rhs) {
		now_pos = rhs.now_pos;
		now_type = rhs.now_type;
	}
	vars() = default;
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
	void push_type ( int now) {
		now_pos.push(now);
		now_type.push(type_token::type);
	}
	void push_float(int now) {
		now_pos.push(now);
		now_type.push(type_token::double_literal);
	}
	type_token now() { return now_type.top(); }
	int pop() {
		int n = now_pos.top();
		now_pos.pop();
		now_type.pop();
		return n;
	}
	int top() { return now_pos.top();}
	size_t size( ) { return now_pos.size(); }
	
};
enum class quat_op {
	label ,
	jmp,
	btrue ,
	bfalse, 
	newvar ,
	func ,
	funcparam ,
	funcend, 
	structdef,
	structend,
	cblock,
	cend,
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
	initlst,initlstend,initlstitem
};
namespace assign_type {
	extern const int normal, add, sub, mul, div, mod, shl, shr, and, or , xor, init;
}


struct parser {
	using quat_info = std::array<int, 3>;
	using quat_type = std::pair<quat_op, quat_info >;
	lex_data data;

	grammar & grm;
	int quat_top;
	vars stack;
	labels label_stack;
	std::map<int, std::pair<int, int> > quat_history;
	std::vector<quat_type> quats;
	std::stack<vars> rec_stack_vars;
	std::stack<labels> rec_stack_labels;
	void add_quat(quat_op, int, int, int);
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
	void binocular_operator(std::string const& op_name, quat_op op,
		std::initializer_list<type_token> && ban);
	void check_contain(std::string const& op_name,std::initializer_list<type_token> && lst);
	void check_not(std::string const& op_name, type_token x);
	void monocular_operator(std::string const& op_name, quat_op op,
		std::initializer_list<type_token> && ban);
	void assign_operator(int ass_type);
	void check_find_label(labels::label const& lb, std::string const& msg);
	parser(lex_data const& d, grammar &g);
	void parse() {
		grm.parse_ll1(data);
	}

};