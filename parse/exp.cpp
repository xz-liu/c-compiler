#include "parse.h"
#include "exp.h"



void rec::parse_E() {
	std::cout << "E ";
	if (now >= data.lex_result.size())return;
	parse_T();
	parse_E1();
}

void rec::parse_E1() {
	std::cout << "E1 ";
	if (now >= data.lex_result.size())return;
	if (data.cmp_token(now, token::add) || data.cmp_token(now, token::sub)) {
		now++;
		parse_T();
		parse_E1();
	}
}

void rec::parse_E2() {
	std::cout << "E2 ";
	if (now >= data.lex_result.size())return;
	if (data.cmp_token(now, token::mul) || data.cmp_token(now, token::div)) {
		now++;
		parse_F();
		parse_E2();
	}
}

void rec::parse_F() {
	std::cout << "F ";
	if (now >= data.lex_result.size()) {
		result = false;
		return;
	};
	if (data.cmp_token(now, token::int_literal) ||
		data.cmp_token(now, token::double_literal) ||
		data.cmp_token(now, token::identifier)) {
		now++; return;
	} else if (data.cmp_token(now, token::lparenthesis)) {
		now++;
		parse_E();
		if (data.cmp_token(now, token::rparenthesis))now++;
		else result = false;
	} else result = false;
}

void rec::parse_T() {
	std::cout << "T ";
	parse_F();
	parse_E2();
}
