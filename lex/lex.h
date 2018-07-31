#pragma once
#include "../basic/basic.h"
#include "token.h"

struct regex_table {
	std::vector<std::pair<std::regex, token>>  table;
	regex_table();
};
struct token_name_type {
	std::map<token, std::string> _name;
	std::string const& operator[](token t) {return _name[t];}
	token_name_type();
};

extern token_name_type token_name;

std::vector<std::pair<token, std::string>>lex(std::string const& s);