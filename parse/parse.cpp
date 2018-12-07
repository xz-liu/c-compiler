#include "parse.h"
#include "graph.h"
#include "../error/error.h"
#include "type.h"
//#define _MYDEBUG_PARSER
#ifdef _MYDEBUG_PARSER
using std::cout;
using std::endl;
#endif

void parser::check_find_label(labels::label const& lb, std::string const& msg) {
	if (lb.second == labels::fail) {
		throw parse_error(msg);
	}
};
void parser::check_contain(std::string const& op_name,
	std::initializer_list<type_token> && lst) {
	for (auto &&x : lst) {
		if (stack.now() == x) {
			throw parse_error(op_name + " operator used on "
				+ data.get_token_name(stack.top()));
		}
	}
};
void parser::check_not(std::string const& op_name, type_token x) {
	if (stack.now() != x) {
		throw parse_error(op_name + " operator used on "
			+ data.get_token_name(stack.top()));
	}
}
void parser::monocular_operator(std::string const& op_name, quat_op op,
	std::initializer_list<type_token> && ban) {
	for (auto &&x : ban) {
		if (stack.now() == x) {
			throw parse_error(op_name + " operator used on "
				+ data.get_token_name(stack.top()));
		}
	}
	int n = stack.pop();
	int newvar = push_tmp_var();
	add_quat(op, n, 0, newvar);

};
void parser::binocular_operator(std::string const& op_name, quat_op op,
	std::initializer_list<type_token> && ban) {
#ifdef _MYDEBUG_PARSER
	//std::cout << "\t--[BINO OP: " << op_name << " " << stack.size() << std::endl;

#endif

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
	add_quat(op, lhs, rhs, nv);
}


void parser::assign_operator(int ass_type) {
	int rhs = stack.pop();
	int lhs = stack.pop();
	stack.push_id(lhs);
	add_quat(quat_op::assign, lhs, rhs, ass_type);
}
void parser::try_place_label(int label) {
	if (label_stack.placed(label))return;
	label_stack.place(label);
	add_quat(quat_op::label, label, 0, 0);
}
;

void parser::add_quat(quat_op op, int v1, int v2, int v3) {
	std::pair<quat_op, quat_info > now = { op,{ v1, v2, v3 } };

//#ifdef _MYDEBUG_PARSER
	std::cout << "[[ GEN QUAT -- " ;
	types::debug_single_quat(now, label_stack, data);
//#endif

	if (quat_top < quats.size())quats[quat_top++] = now;
	else {
		quats.push_back(now);
		quat_top++;
	}
}
void parser::show_quats() {
	
}
void parser::return_to(int i) {
	action_called_cnt = i;
	auto it = quat_history.find(i);
	label_cnt = it->second.first;
	quat_top = it->second.second;
	stack = rec_stack_vars.top();
	rec_stack_vars.pop();
	label_stack = rec_stack_labels.top();
	rec_stack_labels.pop();
}
void parser::new_history(int i) {
	quat_history.insert_or_assign(i, std::make_pair(label_cnt, quat_top));
}

int parser::push_tmp_var() {
	int push = input_data_cnt + tmp_var_cnt;
	stack.push_id(push);
	++tmp_var_cnt;
	return push;
}
int parser::alloc_tmp_var() {
	return input_data_cnt+ tmp_var_cnt++;
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
	grm.assign_action(str, [&](int action_id ,int now) { \
		stack.debug(data) ;\
		if(action_id>=0) quat_history.emplace( action_id ,std::make_pair(label_cnt, quat_top) ) ;  \
		code \
		stack.debug(data);\
	})

#pragma region predefined operations
	_GRAMMAR_ASSIGN_ACT("return_to", {
		//cout << " \t-- call [return_to] , RETURN TO " << action_id <<" STACK "<< rec_stack_vars.size() << endl;
		return_to(action_id);
	});
	_GRAMMAR_ASSIGN_ACT("push_stack", {
		rec_stack_vars.push(stack);
		rec_stack_labels.push(label_stack);
		//cout << " \t-- call [push_stack] , stack cnt" << rec_stack_vars.size() << " STACKNOW CNT" << stack.size()<< endl;
	});
	_GRAMMAR_ASSIGN_ACT("select_stack", {
		rec_stack_vars.pop();
		rec_stack_labels.pop();
		//cout << " \t-- call [select_stack] , stack cnt" << rec_stack_vars.size() << endl;
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
	_GRAMMAR_ASSIGN_ACT("{push_str}", {
		stack.push_str(now);
	});
#pragma endregion 

#pragma region exp op::inc&dec

	_GRAMMAR_ASSIGN_ACT("{@++}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("++ operator can only use on an variable");
		}
		int n = stack.pop();
		int newvar = push_tmp_var();
		add_quat(quat_op::assign, newvar, n, assign_type::normal);
		add_quat(quat_op::inc, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{@--}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("-- operator can only use on an variable");
		}
		int n = stack.pop();
		int newvar = push_tmp_var();
		add_quat(quat_op::assign, newvar, n, assign_type::normal);
		add_quat(quat_op::dec, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{--@}", {
		if (stack.now() != type_token::identifier) {
			throw parse_error("-- operator can only use on an variable");
		}
		int n = stack.top();
		add_quat(quat_op::dec, n,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{++@}", {
		if (stack.now() != type_token::identifier)
			throw parse_error("++ operator can only use on an variable");

		int n = stack.top();
		add_quat(quat_op::inc, n,0,0);
	});

#pragma endregion 

#pragma region exp op:: mono op

	_GRAMMAR_ASSIGN_ACT("{!@}", {
		monocular_operator("!", quat_op::lnot,
			{type_token::double_literal,type_token::string_literal});
	});
	_GRAMMAR_ASSIGN_ACT("{~@}", {
		monocular_operator("~", quat_op::bnot,
		{ type_token::double_literal,type_token::string_literal });
	});
	_GRAMMAR_ASSIGN_ACT("{+@}", {
		monocular_operator("+", quat_op::pos,
		{ type_token::string_literal });
	});
	_GRAMMAR_ASSIGN_ACT("{-@}", {
		monocular_operator("-", quat_op::neg,
		{ type_token::string_literal });
	});
#pragma endregion 

#pragma region  exp op:: bino op

	_GRAMMAR_ASSIGN_ACT("{@*@}", {
		binocular_operator("*",quat_op::mul,{type_token::string_literal});
	});

	_GRAMMAR_ASSIGN_ACT("{@/@}", {
		binocular_operator("/",quat_op::div,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@+@}", {
		binocular_operator("+",quat_op::add,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@-@}", {
		binocular_operator("-",quat_op::sub,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<<@}", {
		binocular_operator("<<",quat_op::shl,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>>@}", {
		binocular_operator(">>",quat_op::shr,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<@}", {
		binocular_operator("<",quat_op::l,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>@}", {
		binocular_operator(">",quat_op::g,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@<=@}", {
		binocular_operator("<=",quat_op::le,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@>=@}", {
		binocular_operator(">=",quat_op::ge,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@==@}", {
		binocular_operator("==",quat_op::e,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@!=@}", {
		binocular_operator("!=",quat_op::ne,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@&@}", {
		binocular_operator("&",quat_op::band,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@|@}", {
		binocular_operator("|",quat_op::bor,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@&&@}", {
		binocular_operator("&",quat_op::land,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@||@}", {
		binocular_operator("||",quat_op::lor,{ type_token::string_literal });
	});

	_GRAMMAR_ASSIGN_ACT("{@[@]}", {
		binocular_operator("[]",quat_op::arrayval,{});
	});

	_GRAMMAR_ASSIGN_ACT("{@.@}", {
		binocular_operator(" . ",quat_op::structval,{});
	});
#pragma endregion 

#pragma region exp op::assign_op
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

#pragma region call 
	_GRAMMAR_ASSIGN_ACT("{call_func_end}", {
		int nv = push_tmp_var();
		add_quat(quat_op::callend, nv, 0, 0);

	});
	_GRAMMAR_ASSIGN_ACT("{call_func_begin}", {
		check_not("call func" ,type_token::identifier);
		int id = stack.pop();
		add_quat(quat_op::call, id,0,0);

	});
	_GRAMMAR_ASSIGN_ACT("{call_func_push}", {
		int n = stack.pop();
		add_quat(quat_op::push, n, 0, 0);
	});
#pragma  endregion

#pragma  region  while_stmt
	_GRAMMAR_ASSIGN_ACT("{while_begin}", {
		int n = push_label(labels::loop_begin);//while begin
		push_label(labels::loop_end);//while end
		add_quat(quat_op::label, n, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{while_check}", {
		int n = stack.pop();
		auto nearest_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(nearest_end, "while_check failed : loop_end notfound");
		add_quat(quat_op::bfalse, nearest_end.first, n, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{while_end}", {
		auto nearest_lb = label_stack.find_nearest(labels::loop_begin);
		check_find_label(nearest_lb, "while_end failed : loop_begin notfound");

		add_quat(quat_op::jmp, nearest_lb.first, 0, 0);
		auto nearest_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(nearest_end, "while_check failed : loop_end notfound");
		try_place_label(nearest_end.first);
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
		add_quat(quat_op::jmp, for_begin, 0, 0);
		add_quat(quat_op::label, loop_begin, 0, 0);
	});

	_GRAMMAR_ASSIGN_ACT("{for_check}", {

		int n = stack.pop();
		labels::label loop_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(loop_end, "for_check failed : loop_end notfound");
		labels::label for_begin = label_stack.find_nearest(labels::for_begin);
		check_find_label(for_begin, "for_check failed : for_begin notfound");
		labels::label for_suf = label_stack.find_nearest(labels::for_suf);
		check_find_label(for_suf, "for_check failed : for_suf notfound");
		add_quat(quat_op::btrue, for_begin.first, n, 0);
		add_quat(quat_op::bfalse, loop_end.first, n, 0);
		try_place_label(for_suf.first) ;

	});
	_GRAMMAR_ASSIGN_ACT("{for_suf}", {
		labels::label loop_begin = label_stack.find_nearest(labels::loop_begin);
		check_find_label(loop_begin, "for_suf failed : loop_begin notfound");
		labels::label for_begin = label_stack.find_nearest(labels::for_begin);
		check_find_label(for_begin, "for_suf failed : for_begin notfound");


		add_quat(quat_op::jmp, loop_begin.first, 0, 0);
		try_place_label(for_begin.first) ;
	});
	_GRAMMAR_ASSIGN_ACT("{for_end}", {
		labels::label loop_end = label_stack.find_nearest(labels::loop_end);
		check_find_label(loop_end, "for_end failed : loop_end notfound");

		labels::label for_suf = label_stack.find_nearest(labels::for_suf);
		check_find_label(for_suf, "for_end failed : for_suf notfound");

		add_quat(quat_op::jmp, for_suf.first, 0, 0);
		try_place_label(loop_end.first) ;
	});
#pragma endregion 

#pragma region if_stmt
	_GRAMMAR_ASSIGN_ACT("{if_begin}", {
		push_label(labels::if_end);
		push_label(labels::else_end);
	});
	_GRAMMAR_ASSIGN_ACT("{if_check}", {
		int exp = stack.pop();
		labels::label if_end = label_stack.find_nearest(labels::if_end);
		check_find_label(if_end, "if_check failed : if_end notfound");
		add_quat(quat_op::bfalse, if_end.first,exp,0);
	});
	_GRAMMAR_ASSIGN_ACT("{if_end}", {
		labels::label if_end = label_stack.find_nearest(labels::if_end);
		check_find_label(if_end, "if_end failed : if_end notfound");
		labels::label else_end = label_stack.find_nearest(labels::else_end);
		check_find_label(else_end, "if_end failed : else_end notfound");
		add_quat(quat_op::jmp, else_end.first, 0, 0);
		try_place_label(if_end.first) ;
	});
	_GRAMMAR_ASSIGN_ACT("{else_end}", {
		labels::label else_end = label_stack.find_nearest(labels::else_end);
		check_find_label(else_end, "else_end failed : else_end notfound");
		try_place_label(else_end.first) ;
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
		try_place_label(switch_end.first) ;
	});

	_GRAMMAR_ASSIGN_ACT("{case_begin}", {
		int ce = push_label(labels::case_end);
		int chr = stack.pop();
		int exp = stack.top();
		int nv = alloc_tmp_var();
		add_quat(quat_op::sub, chr, exp, nv);
		add_quat(quat_op::btrue, ce, nv, 0);
	});

	_GRAMMAR_ASSIGN_ACT("{case_end}", {
		labels::label case_end = label_stack.find_nearest(labels::case_end);
		check_find_label(case_end, "case_end failed : case_end notfound");
		try_place_label(case_end.first) ;
	});

#pragma endregion 

#pragma region break & continue 

	_GRAMMAR_ASSIGN_ACT("{break}", {
		labels::label switch_end = label_stack.find_nearest(labels::switch_end);
		labels::label loop_end = label_stack.find_nearest(labels::loop_end);
		int label_out = std::max(switch_end.first, loop_end.first);
		if(label_out<0) {
			throw parse_error("break with no switch/loop");
		}
		add_quat(quat_op::jmp, label_out, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{continue}", {
		labels::label for_suf = label_stack.find_nearest(labels::for_suf);
		labels::label loop_begin = label_stack.find_nearest(labels::loop_begin);
		int label_out = std::max(loop_begin.first, for_suf.first);
		if (label_out<0) {
			throw parse_error("continue with no for/while");
		}
		add_quat(quat_op::jmp, label_out, 0, 0);
	});

#pragma endregion 

#pragma region var & array def
	_GRAMMAR_ASSIGN_ACT("{int16}", {
		stack.push_type(types::int16);
	});
	_GRAMMAR_ASSIGN_ACT("{uint16}", {
		stack.push_type(types::uint16);
	});
	_GRAMMAR_ASSIGN_ACT("{int32}", {
		stack.push_type(types::int32);
	});
	_GRAMMAR_ASSIGN_ACT("{uint32}", {
		stack.push_type(types::uint32);
	});
	_GRAMMAR_ASSIGN_ACT("{int64}", {
		stack.push_type(types::int64);
	});
	_GRAMMAR_ASSIGN_ACT("{uint64}", {
		stack.push_type(types::uint64);
	});
	_GRAMMAR_ASSIGN_ACT("{char8}", {
		stack.push_type(types::char8);
	});
	_GRAMMAR_ASSIGN_ACT("{uchar8}", {
		stack.push_type(types::uchar8);
	});
	_GRAMMAR_ASSIGN_ACT("{float32}", {
		stack.push_type(types::float32);
	});
	_GRAMMAR_ASSIGN_ACT("{float64}", {
		stack.push_type(types::float64);
	});
	_GRAMMAR_ASSIGN_ACT("{void}", {
		stack.push_type(types::void_type);
	});
	_GRAMMAR_ASSIGN_ACT("{struct_var}", {
		stack.push_type(types::struct_id(stack.pop()));
	});
	_GRAMMAR_ASSIGN_ACT("{def_array}",{
		// now is int_const
		int id = stack.pop();
		int ty = stack.top();
		stack.push_id(id);
		add_quat(quat_op::newvar, id, ty, now);
	});

	_GRAMMAR_ASSIGN_ACT("{var_def_end}",{
		int id = stack.pop();
		int ty = stack.top();
		add_quat(quat_op::newvar, id, ty, -1);
	});

	_GRAMMAR_ASSIGN_ACT("{var_init_end}", {
		int exp = stack.pop();
		int id = stack.pop();
		int ty = stack.top();
		add_quat(quat_op::newvar, id, ty, 0);
		add_quat(quat_op::assign, id, exp, assign_type::init);
	});

	_GRAMMAR_ASSIGN_ACT("{init_list_begin}", {
		int ilist_id = push_tmp_var();
		add_quat(quat_op::initlst, ilist_id, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{init_list_item}",{
		int item = stack.pop();
		int lstid = stack.top();
		add_quat(quat_op::initlstitem, lstid, item, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{init_list_end}",{
		int lstid = stack.pop();
		int id = stack.top();
		add_quat(quat_op::initlstend, lstid, 0, 0);
		add_quat(quat_op::assign, id, lstid, assign_type::init);
	});

	_GRAMMAR_ASSIGN_ACT("{arr_init_str}", {
		int str = stack.pop();
		int id = stack.top();
		add_quat(quat_op::assign, id, str, assign_type::init);
	});
	_GRAMMAR_ASSIGN_ACT("{def_array_end}", {
		stack.pop();// pop id
	});

	_GRAMMAR_ASSIGN_ACT("{var_def_list_end}", {
		stack.pop();// pop type
	});

#pragma endregion 

#pragma region struct def
	
	_GRAMMAR_ASSIGN_ACT("{struct_begin}", {
		int id = stack.top();
		add_quat(quat_op::structdef, id, 0, 0);
	});

	_GRAMMAR_ASSIGN_ACT("{struct_end}", {
		int id = stack.pop();
		add_quat(quat_op::structend, id, 0, 0);
	});

#pragma endregion 

#pragma region func decl & def
	_GRAMMAR_ASSIGN_ACT("{func_begin}", {
		int id = stack.pop();
		int ty = stack.pop();
		stack.push_id(id);
		add_quat(quat_op::func, id, ty, 0);
	});

	_GRAMMAR_ASSIGN_ACT("{func_end}", {
		//int ret = stack.pop();
		int ed = stack.pop();
		add_quat(quat_op::funcend, ed, 0, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{param_var}", {
		int id = stack.pop();
		int ty = stack.pop();
		add_quat(quat_op::funcparam, id, ty, 0);
	});
	_GRAMMAR_ASSIGN_ACT("{param_array}", {
		int id = stack.pop();
		int ty = stack.pop();
		add_quat(quat_op::funcparam, id, ty, 1);
	});

	_GRAMMAR_ASSIGN_ACT("{return}", {
		add_quat(quat_op::ret,0,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{return@}", {
		int n = stack.pop();
		add_quat(quat_op::retval, 0, 0, n);
	});

#pragma endregion 

#pragma region codeblock
	_GRAMMAR_ASSIGN_ACT("{code_block}",{
		add_quat(quat_op::cblock,0,0,0);
	});

	_GRAMMAR_ASSIGN_ACT("{code_block_end}",{
		add_quat(quat_op::cend,0,0,0);
	});
#pragma endregion 
}

