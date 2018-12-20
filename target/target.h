#pragma once
#include "../lex/lex.h"
#include "../parse/type.h"

struct target {
	lex_data const & data;//各种变量表、数组表、常数表等
	symbols & sym;
	std::string dseg;
	std::string cseg_begin;
	std::string cseg;
	std::string cseg_end;
	std::map<int,std::string> id_name;
	void work();//生成目标代码
	void init_of_var(int id, int id_to_init);
	std::string name_of(int id, scope::handle_scope h_curr);//通过id获取变量名字
	target(lex_data const& d, symbols & sy);
	std::string assembly(){//将代码组合
		return dseg + cseg_begin + cseg + cseg_end;
	}
};
