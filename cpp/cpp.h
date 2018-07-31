#pragma once
#include "../basic/basic.h"
#include "../lex/lex.h"

struct cpp {
	cpp();
	std::vector<token_pair> operator()(std::string const& dir, std::istream &item, std::ostream &out);
private:
	std::map<std::string, std::string> mdefines;
};