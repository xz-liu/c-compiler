#pragma once
#include "../basic/basic.h"
#include "token.h"

struct regex_table {
	std::vector<std::pair<std::regex, token>>  table;
	std::map<token,std::string> name;
	regex_table();
};

std::vector<std::pair<token, std::string>>lex(std::string const& s);