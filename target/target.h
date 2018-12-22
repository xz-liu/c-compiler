#pragma once
#include "../lex/lex.h"
#include "../parse/type.h"

struct target {

	struct univ_var {
		enum type {
			array_val,
			normal
		}ty;
		target* tg;
		std::string pos_id;
		std::string normal_var;
		operator std::string() {
			if (ty == array_val) {
				tg->cseg += "mov esi," + pos_id + "\n";
				return normal_var + "[esi]";
			} else return normal_var;
		}
		univ_var() :ty(normal){}
		univ_var(univ_var const&) = default;
		univ_var& operator= (std::string const& s) {
			ty = normal;
			normal_var = s;
			return *this;
		}
		univ_var(std::string const& s) :normal_var(s), ty(normal) {}
		univ_var(target *t, std::string const& pos_id, std::string const& arr_id)
			:tg(t), normal_var(arr_id), pos_id(pos_id), ty(array_val) {}
	};

	lex_data const & data;
	symbols & sym;
	std::string incl;
	std::string struct_def;
	std::string dseg;
	std::string cseg_begin;
	std::string cseg;
	std::string cseg_end;
	std::map<std::pair<int,scope::handle_scope>, univ_var> id_name;
	std::map<int, univ_var> const_name;
	std::map < scope::handle_scope, univ_var> return_value_names;
	std::map<int, bool> has_return_command;
	univ_var& return_value_of(int curr_call_id);
	void work();
	int curr_call_id,curr_push_pos,curr_funcdef_id;

	//void init_of_var(int id, int id_to_init);
	univ_var& insert_retval( scope::handle_scope h_curr);
	univ_var & name_of(int id, scope::handle_scope h_curr,bool is_array_param =false);
	univ_var & name_of_struct_member(int id, int s_id, int f_id, scope::handle_scope h_curr);
	univ_var & name_of_array_member(int id,int arr_id, int pos_id, scope::handle_scope h_curr);
	target(lex_data const& d, symbols & sy);
	std::string assembly(){
		return incl+ struct_def+ dseg + cseg_begin + cseg + cseg_end;
	}
};

std::string operator+(std::string const&lhs, target::univ_var& rhs);
std::string operator+(target::univ_var& lhs, std::string const&rhs);
