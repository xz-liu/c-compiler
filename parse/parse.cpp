#include "parse.h"
#include "graph.h"
#include "../error/error.h"

namespace assign_type {
	const static int normal = 1,
		add = 2,
		sub = 3,
		mul = 4,
		div = 5,
		mod = 6,
		shl = 7,
		shr = 8,
		and = 9,
		or = 10,
		xor = 11;
}
void parser::add_quad(quad_op op, int v1, int v2, int v3) {
	std::pair<quad_op, quad_info > now = { op,{ v1, v2, v3 } };
	if (quad_top < quads.size())quads[quad_top++] = now;
	else {
		quads.push_back(now);
		quad_top++;
	}
}
void parser::return_to(int i) {
	action_called_cnt = i;
	auto it = quad_history.find(i);
	label_cnt = it->second.first;
	quad_top = it->second.second;
	stack = rec_stack_vars.top();
	rec_stack_vars.pop();
	label_stack = rec_stack_labels.top();
	rec_stack_labels.pop();
}
void parser::new_history(int i) {
	quad_history.insert_or_assign(i, std::make_pair(label_cnt, quad_top));
}
int parser::push_tmp_var() {
	stack.push_id(input_data_cnt + tmp_var_cnt);
	return tmp_var_cnt++;
}
int parser::alloc_tmp_var() {
	return tmp_var_cnt++;
}
int parser::push_label(labels::label_type ty) {
	label_stack.push(ty,label_cnt);
	return label_cnt++;
}
void parser::push_label(int i,labels::label_type ty) {
	label_stack.push(ty,i);
}
int parser::pop_label() {
	auto label = label_stack.pop();
	return label.first;
}
parser::parser(lex_data const& d, grammar & g)
	:data(d), grm(g), action_called_cnt(0), label_cnt(0)
	, tmp_var_cnt(0), input_data_cnt(d.lex_result.size()) {

#define _GRAMMAR_ASSIGN_ACT(str,code) \
	grm.assign_action(str, [&](int action_id ,int now) code)

#pragma region predefined operations
	_GRAMMAR_ASSIGN_ACT("return_to", {
		return_to(action_id);
	});
	_GRAMMAR_ASSIGN_ACT("push_stack", {
		rec_stack_vars.push(stack);
		rec_stack_labels.push(label_stack);
	});
	_GRAMMAR_ASSIGN_ACT("select_stack", {
		rec_stack_vars.pop();
		rec_stack_labels.pop();
	});
#pragma endregion 

#pragma region basic push&pop operations
	_GRAMMAR_ASSIGN_ACT("{pop_top}", {
		stack.pop();
	});
	_GRAMMAR_ASSIGN_ACT("{push_id}", {
		stack.push_id(now);
	});
	_GRAMMAR_ASSIGN_ACT("{push_char}", {
		stack.push_char(now);
	});
	_GRAMMAR_ASSIGN_ACT("{push_float}", {
		stack.push_float(now);
	});
	_GRAMMAR_ASSIGN_ACT("{push_int}", {
		stack.push_int(now);
	});
#pragma endregion 

#pragma region check&&throw
	auto check_contain = [&](std::string const& op_name,
		std::initializer_list<type_token> && lst) {
		for (auto &&x : lst) {
			if (stack.now() == x) {
				throw parse_error(op_name + " operator used on "
					+ data.get_token_name(stack.top()));
			}
		}
	};
	auto check_not = [&](std::string const& op_name, type_token x) {
		if (stack.now() != x) {
			throw parse_error(op_name + " operator used on "
				+ data.get_token_name(stack.top()));
		}
	};
#pragma endregion

#pragma region exp op::inc&dec

	_GRAMMAR_ASSIGN_ACT("{@++}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("++ operator can only use on an variable");
		}
		int n = stack.pop();
		int newvar = push_tmp_var();
		add_quad(quad_op::assign, newvar, n, assign_type::normal);
		add_quad(quad_op::inc, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{@--}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("-- operator can only use on an variable");
		}
		int n = stack.pop();
		int newvar = push_tmp_var();
		add_quad(quad_op::assign, newvar, n, assign_type::normal);
		add_quad(quad_op::dec, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{--@}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("-- operator can only use on an variable");
		}
		int n = stack.top();
		add_quad(quad_op::dec, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{++@}", {
		if (stack.now() != type_token::identifier)
			throw parse_error("++ operator can only use on an variable");

		int n = stack.top();
		add_quad(quad_op::inc, n,0,0);
	});

#pragma endregion 

#pragma region exp op:: mono op
	auto monocular_operator = [&](std::string const& op_name, quad_op op,
		std::initializer_list<type_token> && ban) {
		for (auto &&x : ban) {
			if (stack.now() == x) {
				throw parse_error(op_name + " operator used on "
					+ data.get_token_name(stack.top()));
			}
		}
		int n = stack.pop();
		int newvar = push_tmp_var();
		add_quad(op, n, 0, newvar);

	};
	_GRAMMAR_ASSIGN_ACT("{!@}", {
		monocular_operator("!", quad_op::lnot,
			{type_token::double_literal,type_token::string_literal});
	});
	_GRAMMAR_ASSIGN_ACT("{~@}", {
		monocular_operator("~", quad_op::bnot,
		{ type_token::double_literal,type_token::string_literal });
	});
	_GRAMMAR_ASSIGN_ACT("{+@}", {
		monocular_operator("+", quad_op::pos,
		{ type_token::string_literal });
	});
	_GRAMMAR_ASSIGN_ACT("{-@}", {
		monocular_operator("-", quad_op::neg,
		{ type_token::string_literal });
	});
#pragma endregion 

#pragma region  exp op:: bino op
	auto binocular_operator = [&](std::string const& op_name, quad_op op,
		std::initializer_list<type_token> && ban) {
		for (auto &&x : ban) {
			if (stack.now() == x) {
				throw parse_error(op_name + " operator used on "
					+ data.get_token_name(stack.top()));
			}
		}
		int rhs = stack.pop();
		for (auto &&x : ban) {
			if (stack.now() == x) {
				throw parse_error(op_name + " operator used on "
					+ data.get_token_name(stack.top()));
			}
		}
		int lhs = stack.pop();
		int nv = push_tmp_var();
		add_quad(op, lhs, rhs, nv);
	};
	_GRAMMAR_ASSIGN_ACT("{@*@}", {
		binocular_operator("*",quad_op::mul,{type_token::string_literal});
	});

	_GRAMMAR_ASSIGN_ACT("{@/@}", {
		binocular_operator("/",quad_op::div,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@+@}", {
		binocular_operator("+",quad_op::add,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@-@}", {
		binocular_operator("-",quad_op::sub,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<<@}", {
		binocular_operator("<<",quad_op::shl,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>>@}", {
		binocular_operator(">>",quad_op::shr,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<@}", {
		binocular_operator("<",quad_op::l,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>@}", {
		binocular_operator(">",quad_op::g,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<=@}", {
		binocular_operator("<=",quad_op::le,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>=@}", {
		binocular_operator(">=",quad_op::ge,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@==@}", {
		binocular_operator("==",quad_op::e,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@!=@}", {
		binocular_operator("!=",quad_op::ne,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@&@}", {
		binocular_operator("&",quad_op::band,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@|@}", {
		binocular_operator("|",quad_op::bor,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@&&@}", {
		binocular_operator("&",quad_op::land,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@||@}", {
		binocular_operator("||",quad_op::lor,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{{@[@}}", {
		binocular_operator("[]",quad_op::arrayval,{});
	});

	_GRAMMAR_ASSIGN_ACT("{{@.@}", {
		binocular_operator(" . ",quad_op::structval,{});
	});
#pragma endregion 

#pragma region exp op::assign_op
	auto assign_operator = [&](int ass_type) {
		int rhs = stack.pop();
		int lhs = stack.pop();
		add_quad(quad_op::assign, lhs, rhs, ass_type);
	};
	_GRAMMAR_ASSIGN_ACT("{@=@}", {
		assign_operator(assign_type::normal);
	});

	_GRAMMAR_ASSIGN_ACT("{@+=@}", {
		assign_operator(assign_type::add);
	});

	_GRAMMAR_ASSIGN_ACT("{@-=@}", {
		assign_operator(assign_type::sub);
	});

	_GRAMMAR_ASSIGN_ACT("{@*=@}", {
		assign_operator(assign_type::mul);
	});

	_GRAMMAR_ASSIGN_ACT("{@/=@}", {
		assign_operator(assign_type::div);
	});

	_GRAMMAR_ASSIGN_ACT("{@%=@}", {
		assign_operator(assign_type::mod);
	});

	_GRAMMAR_ASSIGN_ACT("{@<<=@}", {
		assign_operator(assign_type::shl);
	});

	_GRAMMAR_ASSIGN_ACT("{@>>=@}", {
		assign_operator(assign_type::shr);
	});

	_GRAMMAR_ASSIGN_ACT("{@=@}", {
		assign_operator(assign_type::normal);
	});

	_GRAMMAR_ASSIGN_ACT("{@&=@}", {
		assign_operator(assign_type::and);
	});

	_GRAMMAR_ASSIGN_ACT("{@|=@}", {
		assign_operator(assign_type:: or );
	});

	_GRAMMAR_ASSIGN_ACT("{@^=@}", {
		assign_operator(assign_type::xor);
	});
#pragma endregion 

#pragma region call&return
	_GRAMMAR_ASSIGN_ACT("{call_func}", {
		check_not("call func" ,type_token::identifier);
		int n = stack.pop();
		add_quad(quad_op::call, n,0,0);

	});
	_GRAMMAR_ASSIGN_ACT("{call_func_push}", {
		int n = stack.top();
		add_quad(quad_op::push, n, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{return}", {
		add_quad(quad_op::ret,0,0,0);
	});
	_GRAMMAR_ASSIGN_ACT("{return@}", {
		int n = stack.pop();
		int nv = push_tmp_var();
		add_quad(quad_op::assign, nv, n, assign_type::normal);
	});
#pragma  endregion

	auto check_find_label = [&](labels::label const& lb, std::string const& msg) {
		if (lb.second == labels::fail) {
			throw parse_error(msg);
		}
	};

#pragma  region  while_stmt
	_GRAMMAR_ASSIGN_ACT("{while_begin}", {
		int n = push_label(labels::loop_begin);//while begin
		push_label(labels::loop_end);//while end
		add_quad(quad_op::label, n, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{while_check}", {
		int n = stack.pop();
		auto nearest_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(nearest_end, "while_check failed : loop_end notfound");
		add_quad(quad_op::bfalse, nearest_end.first, n, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{while_end}", {
		auto nearest_lb = label_stack.find_nearest(labels::loop_begin);
		check_find_label(nearest_lb, "while_end failed : loop_begin notfound");

		add_quad(quad_op::jmp, nearest_lb.first, 0, 0);
	});
#pragma endregion 

#pragma region  for_stmt
	/*
		init code
		jmp for_begin
		loop_begin
		check_data
			true -> for_begin
			false -> loop_end
		for_suf
		suf data
		jmp check_data
		for_begin
		jmp for_suf
		loop_end
	 */
	_GRAMMAR_ASSIGN_ACT("{for_init}", {
		int loop_begin = push_label(labels::loop_begin);
		push_label(labels::for_suf);
		push_label(labels::loop_end);
		int for_begin = push_label(labels::for_begin);
		add_quad(quad_op::jmp, for_begin, 0, 0);
		add_quad(quad_op::label, loop_begin, 0, 0);
	});

	_GRAMMAR_ASSIGN_ACT("{for_check}", {

		int n = stack.pop();
		labels::label loop_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(loop_end, "for_check failed : loop_end notfound");
		labels::label for_begin = label_stack.find_nearest(labels::for_begin);
		check_find_label(for_begin, "for_check failed : for_begin notfound");
		labels::label for_suf = label_stack.find_nearest(labels::for_suf);
		check_find_label(for_suf, "for_check failed : for_suf notfound");
		add_quad(quad_op::btrue, for_begin.first, n, 0);
		add_quad(quad_op::bfalse, loop_end.first, n, 0);
		add_quad(quad_op::label, for_suf.first, 0, 0);

	});
	_GRAMMAR_ASSIGN_ACT("{for_suf}", {
		labels::label loop_begin = label_stack.find_nearest(labels::loop_begin);
		check_find_label(loop_begin, "for_suf failed : loop_begin notfound");
		labels::label for_begin = label_stack.find_nearest(labels::for_begin);
		check_find_label(for_begin, "for_suf failed : for_begin notfound");


		add_quad(quad_op::jmp, loop_begin.first, 0, 0);
		add_quad(quad_op::label, for_begin.first, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{for_end}", {
		labels::label loop_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(loop_end, "for_end failed : loop_end notfound");

		labels::label for_suf = label_stack.find_nearest(labels::for_suf);
		check_find_label(for_suf, "for_end failed : for_suf notfound");

		add_quad(quad_op::jmp, for_suf.first, 0, 0);
		add_quad(quad_op::label, loop_end.first, 0, 0);
	});
#pragma endregion 

#pragma region if_stmt
	_GRAMMAR_ASSIGN_ACT("{if_begin}", {
		push_label(labels::if_end);
		push_label(labels::else_end);
	});
	_GRAMMAR_ASSIGN_ACT("{if_check}", {
		labels::label if_end = label_stack.find_nearest(labels::if_end);
		check_find_label(if_end, "if_check failed : if_end notfound");
		add_quad(quad_op::bfalse, if_end.first,0,0);
	});
	_GRAMMAR_ASSIGN_ACT("{if_end}", {
		labels::label if_end = label_stack.find_nearest(labels::if_end);
		check_find_label(if_end, "if_end failed : if_end notfound");
		labels::label else_end = label_stack.find_nearest(labels::else_end);
		check_find_label(else_end, "if_end failed : else_end notfound");
		add_quad(quad_op::jmp, else_end.first, 0, 0);
		add_quad(quad_op::label, if_end.first, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{else_end}", {
		labels::label else_end = label_stack.find_nearest(labels::else_end);
		check_find_label(else_end, "else_end failed : else_end notfound");
		add_quad(quad_op::label, else_end.first, 0, 0);
	});

#pragma endregion 


#pragma region switch 

	_GRAMMAR_ASSIGN_ACT("{switch_begin}", {
		push_label(labels::switch_end);
	});

	_GRAMMAR_ASSIGN_ACT("{switch_end}", {
		labels::label switch_end = label_stack.find_nearest(labels::switch_end);
		check_find_label(switch_end, "switch_end failed : switch_end notfound");
		stack.pop();
		add_quad(quad_op::label,switch_end.first,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{case_begin}", {

		int ce = push_label(labels::case_end);
		int chr = stack.pop();
		int exp = stack.pop();
		int nv = alloc_tmp_var();
		add_quad(quad_op::sub, chr, exp, nv);
		add_quad(quad_op::btrue, ce, nv, 0);

	});

	_GRAMMAR_ASSIGN_ACT("{case_end}", {
		labels::label case_end = label_stack.find_nearest(labels::case_end);
		check_find_label(case_end, "case_end failed : case_end notfound");
		add_quad(quad_op::label, case_end.first, 0, 0);
	});

#pragma endregion 

#pragma region break & continue 

	_GRAMMAR_ASSIGN_ACT("{break}", {

	});
	_GRAMMAR_ASSIGN_ACT("{continue}", {

	});

#pragma endregion 
}
