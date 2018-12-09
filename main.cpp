
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"
#include "parse\parse.h"
#include "parse/exp.h"
#include "parse/type.h"

//

void debug_string(std::string const& s) {
	static grammar grm;
	using std::cout;
	using std::endl;
	lex_data data_c(s);
	//cout << grm.parse_ll1(data_c) << endl;
	data_c.debug();
	parser parse(data_c, grm);
	parse.parse();
	symbols::debug_quat(parse.quats, parse.label_stack, data_c);
	cout << " -------------------------" << endl;
	symbols sym(parse);
	sym.debug_quat(sym.quats, parse.label_stack, data_c);
}

int main() {
	try {
		std::ifstream ifs("debug.c");
		std::string s, c;
		freopen("output.txt", "w", stdout);
		while (std::getline(ifs, s))c += s;
		debug_string(c);
		std::cout << "DONE" << std::endl;
	}catch(std::exception& e) {
		std::cout << e.what();
	}
	//while (1);
	return 0;
}