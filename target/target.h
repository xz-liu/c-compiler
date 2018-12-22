#pragma once
#include "../lex/lex.h"
#include "../parse/type.h"

struct target {

	struct univ_var {
		enum type {
			array_val,
			normal,
			param_array_val
		}ty;
		target* tg;
		std::string pos_id;
		std::string normal_var;
		std::string ptr_type;
		int type_size;
		std::string reg(std::string which="a") {
			std::string real_reg;
			switch (type_size) {
			case 1:
				real_reg = which + "l";
				break;
			case 2:
				real_reg = which + "x"; break;
			case 4:
			case 8:
				real_reg = "e"+ which + "x"; break;
			}
			tg->cseg += "xor " + real_reg + "," + real_reg + "\n";
			return real_reg;
		}
		operator std::string() {
			if (ty == array_val) {
				tg->cseg += "mov esi," + pos_id + "\n";
				return ptr_type+ normal_var + "["+std::to_string(type_size)+"*esi]";
			} else if (ty== param_array_val) {
				tg->cseg += "mov esi," + pos_id + "\n";
				tg->cseg += "mov ebx,[" + normal_var + "]\n";
				return ptr_type + "[ebx+" + std::to_string(type_size) + "*esi]";
			} else return normal_var;
		}
		univ_var() :ty(normal){}
		univ_var(univ_var const&) = default;
		univ_var& operator= (std::string const& s) {
			ty = normal;
			normal_var = s;
			type_size = s.back() - '0';
			return *this;
		}
		univ_var(std::string const& s) {
			this->operator=(s);
		}
		univ_var(target *t, std::string const& pos_id, std::string const& arr_id, bool is_param, int type_size)
			:tg(t), normal_var(arr_id), pos_id(pos_id),type_size(type_size) {
			if (is_param)ty = param_array_val;
			else { ty = array_val; }
			switch (type_size) {
			case 1:ptr_type = "byte ptr "; break;
			case 2:ptr_type = "word ptr "; break;
			case 4:case 8:
				ptr_type = "dword ptr "; break;
			}
		}
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
