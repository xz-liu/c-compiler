#pragma once
#include "../basic/basic.h"
#include "token.h"

struct regex_table {
	std::vector<std::pair<std::regex, token>>  table;
	regex_table();
};
struct token_name_type {
	std::map<token, std::string> _name;
	std::string const& operator[](token t) { return _name[t]; }
	std::string const& operator[](int t) { return _name[token(t)]; }
	token_name_type();
};

extern token_name_type token_name;
typedef std::pair<token, std::string> token_pair;
typedef std::pair<token, std::any> token_item;
typedef std::pair<type_token, size_t> token_P2;

//template< class T> assign_val(token_item const& it, T& val) {
//	try {
//		val = std::any_cast<float>(a);
//		switch (it.first) {
//		case token::char_literal:
//			val = std::any_cast<char>(it.second); break;
//		case token::string_literal:
//			val = std::any_cast<std::string>(it.second); break;
//		case token::double_literal:
//			val = std::any_cast<double>(it.second); break;
//		case token::int_literal:
//			val = std::any_cast<int64_t>(it.second); break;
//		case token::identifier:
//
//			val = std::any_cast<char>(it.second); break;
//		default:
//			break;
//		}
//	} catch (const std::bad_any_cast& e) {
//		std::cout << e.what() << '\n';
//	}
//}

void assign_item(token_item &it, std::string const& s);

std::vector<token_P2>
lex(std::string const& s,
	std::vector<std::string	>& vlit_str,
	std::vector<std::int64_t>& vlit_int,
	std::vector<double		>& vlit_dbl,
	std::vector<char		>& vlit_chr,
	std::vector<std::string	>& vlit_idt,
	std::vector<std::string	>& vlit_file

);