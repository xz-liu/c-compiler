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
	code_cnt = it->second.first;
	quad_top = it->second.second;
	stack = stack_quad.top();
	stack_quad.pop();
}
void parser::new_history(int i) {
	quad_history.insert_or_assign(i, std::make_pair(code_cnt, quad_top));
}
int parser::push_tmp_var() {
	++tmp_var_cnt;
	stack.push_id(input_data_cnt + tmp_var_cnt);
	return tmp_var_cnt;
}
parser::parser(lex_data const& d, grammar & g)
	:data(d), grm(g), action_called_cnt(0), code_cnt(0)
	, tmp_var_cnt(0), input_data_cnt(d.lex_result.size()) {

#define _GRAMMAR_ASSIGN_ACT(str,code) \
	grm.assign_action(str, [&](int action_id ,int now) code)
	_GRAMMAR_ASSIGN_ACT("return_to", {
		return_to(action_id);
	});
	_GRAMMAR_ASSIGN_ACT("push_stack", {
		stack_quad.push(stack);
	});
	_GRAMMAR_ASSIGN_ACT("select_stack", {
		stack_quad.pop();
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
	auto binocular_operator = [&](std::string const& op_name, quad_op op,
		std::initializer_list<type_token> && ban) {
		int nv = push_tmp_var();
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

}
