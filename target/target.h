#pragma once
#include "../lex/lex.h"
#include "../parse/type.h"

struct target {
	lex_data const & data;
	symbols & sym;
	std::string incl;
	std::string struct_def;
	std::string dseg;
	std::string cseg_begin;
	std::string cseg;
	std::string cseg_end;
	std::map<std::pair<int,scope::handle_scope>,std::string> id_name;
	std::map<int, std::string> const_name;
	std::map < scope::handle_scope, std::string> return_value_names;
	struct univ_var {
		enum var_cat {
			auto_var,
			global_var
		};
		operator std::string();
		
	};

	std::string return_value_of(int curr_call_id);
	void work();
	int curr_call_id,curr_push_pos;
	//void init_of_var(int id, int id_to_init);
	std::string insert_retval( scope::handle_scope h_curr);
	std::string name_of(int id, scope::handle_scope h_curr);
	target(lex_data const& d, symbols & sy);
	std::string assembly(){
		return incl+ struct_def+ dseg + cseg_begin + cseg + cseg_end;
	}
};
