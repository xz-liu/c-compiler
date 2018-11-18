#pragma once
#include "graph.h"

struct quad {
	int op[3];
	token op_type;
};
struct rec {
	int now;
	bool result;
	lex_data const& data;
	rec(lex_data const& d) :data(d), now(0), result(true) {}
	bool good() {
		return result&&now >= data.lex_result.size();
	}
	void parse_E();
	void parse_E1();
	void parse_E2();
	void parse_F();
	void parse_T();
};

struct LL1 {
	std::map<std::pair<char, token>, std::string> ll1_table;

	int now;
	bool result;
	std::string& ll1(char c, token t) {
		return ll1_table[std::make_pair(c, t)];
	}
	auto find_ll1(char c, token t) {
		return ll1_table.find(std::make_pair(c, t));
	}
	bool good() {
		return result&&now >= data.lex_result.size();
	}
	lex_data const& data;
	LL1(lex_data const& d) :data(d), now(0), result(true) {
		std::vector<token> vec1 =
		{ token::int_literal,
			token::double_literal,
			token::identifier,
			token::lparenthesis },
			vec2 = { token::add,token::sub },
			vec3 = { token::rparenthesis,token::dummy },
			vec4 = vec1,
			vec5 = { token::div,token::mul },
			vec6 = { token::add,token::sub,token::rparenthesis,token::dummy },
			vec7 = { token::int_literal,
				token::double_literal,
				token::identifier },
			vec8 = { token::lparenthesis };

		ll1('E', token::identifier) =
			ll1('E', token::double_literal) =
			ll1('E', token::int_literal) =
			ll1('E', token::lparenthesis) = "Te";
		ll1('e', token::add) = ll1('e', token::sub)
			= "+Te";
		ll1('e', token::rparenthesis) = ll1('e', token::dummy) = "";
		ll1('T', token::identifier) =
			ll1('T', token::double_literal) =
			ll1('T', token::int_literal) =
			ll1('T', token::lparenthesis) = "Ft";
		ll1('t', token::add) = ll1('t', token::sub) =
			ll1('t', token::rparenthesis) = ll1('t', token::dummy) = "";
		ll1('t', token::mul) = ll1('t', token::div) = "*Ft";
		ll1('F', token::identifier) =
			ll1('F', token::double_literal) =
			ll1('F', token::int_literal) = "i";
		ll1('F', token::lparenthesis) = "(E)";


	}

	void parse() {
		std::stack<char> sta;
		sta.push('#');
		sta.push('E');
		char t = sta.top();
		while (t != '#') {
			if (t == 'i' && (data.cmp_token(now, token::int_literal) ||
				data.cmp_token(now, token::double_literal) ||
				data.cmp_token(now, token::identifier))) {
				sta.pop();
				now++;
			} else if (t == '('&&data.cmp_token(now, token::lparenthesis)) {
				sta.pop();
				now++;
			} else if (t == ')'&&data.cmp_token(now, token::rparenthesis)) {
				sta.pop();
				now++;
			} else if (t == '*' && (data.cmp_token(now, token::mul) || data.cmp_token(now, token::div))) {
				sta.pop();
				now++;
			} else if (t == '+' && (data.cmp_token(now, token::add) || data.cmp_token(now, token::sub))) {
				sta.pop();
				now++;
			} else if (std::string("i+*()").find(t)>=0) {
				result = false;
				std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
				break;
				
			}else {
				auto r = find_ll1(t, data.get_token(now));
				if (r != ll1_table.end()) {
					std::cout << t << ", " << token_name[data.get_token(now)] << "-> '" << r->second <<"'" << std::endl;
					sta.pop();
					for (int i = r->second.size() - 1; i >= 0; i--) {
						sta.push(r->second[i]);
					}
				} else {
					result = false;
					std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
					break;
				}
			} 
			t = sta.top();
		}
	}

};



struct parser {
	lex_data const& data;
	grammar grm;
	ast result;
	parser(lex_data const& d):data(d){}
	void parse();
	//bool parse(ast::ast_ptr pos,int now, std::string const& exp_s);

};