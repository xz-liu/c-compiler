
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
	sym.debug();
}
void handle() {
	std::set<int64_t> dag;

	auto h=[&](int now, symbols & syn, lex_data & data, scope::handle_scope hscope) {
	if (syn.is_const(now, data)) {// const 
		symbols::type ty = syn.get_const_type(now, data);
		if (ty.first == symbols::int32) {
			//int const
			int64_t val = data.get_int(now);
			//insert your code here
			if(dag.find(val)==dag.end()) {
				std::cout << "NONONO" << std::endl;
			}

		} else if (ty.first == symbols::char8) {
			if (ty.second >= 1) {
				//string 
				std::string s = data.get_str(now);
			} else {
				//char
				char c = data.get_char(now);
			}
		} else {
			// ....
		}
	} else { // id
			 // 当前id的作用域
		scope::handle_scope hid = hscope->find_handle_of_id(now, data);
		int index = hid->get_index(now, data);
		switch (hid->get_type_of_id(now, data)) {
		case scope::struct_type:
		{
			syn.struct_list[index];//....
		}
		case scope::func:
		{
			syn.func_list[index];//....
		}
		case scope::variable:
		{
			auto v=	syn.var_list[index];//....
			//h(v.first.first.first, syn, data, hscope);
		}
		}
	}
};

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



void cpp(std::ifstream & ifs) {
	std::map<std::string, std::string> def;
	std::string curr;
	while(getline(ifs,curr)) {
		std::regex INCLUDE(R"([ ]*#[ ]*include[ ]*<.*>)");
		if(curr.size()) {
		}
	}
}