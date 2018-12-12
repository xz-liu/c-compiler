
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#include "lex\lex.h"
#include "error\error.h"
#include "parse\parse.h"
#include "parse/exp.h"
#include "parse/type.h"
//#define _MYDEBUG_NOCATCH
//
void debug_string(std::string const& s,std::vector<int> const& vec) {
	static grammar grm;
	using std::cout;
	using std::endl;
	lex_data data_c(s,vec);
	//cout << grm.parse_ll1(data_c) << endl;
	data_c.debug();
	parser parse(data_c, grm);
	parse.parse();
	symbols::debug_quat(parse.quats, parse.label_stack, data_c);
	cout << " -------------------------" << endl;
	symbols sym(parse);
	sym.debug_quat(sym.quats, parse.label_stack, data_c);
}
void handle_now( int now ,symbols const& syn,scope::handle_scope hscope) {
	if(syn.is)
}

int main() {
#ifndef _MYDEBUG_NOCATCH
	try {
#endif
		std::ifstream ifs("debug.c");
		std::string s, c;
		std::vector<int> vec;
		int cnt = 0;
		freopen("output.txt", "w", stdout);
		while (std::getline(ifs, s)) {
			vec.push_back(cnt);
			c += s;
			cnt += s.size();
		}
		vec.push_back(cnt);
		debug_string(c,vec);
		std::cout << "DONE" << std::endl;
#ifndef _MYDEBUG_NOCATCH
	}catch(std::exception& e) {
		std::cout << e.what();
	}
#endif
	//while (1);
	return 0;
}

