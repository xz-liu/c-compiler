#pragma once
#include "graph.h"
#include "parse.h"

struct scope 
:public std::enable_shared_from_this<scope>{
	enum id_type {
		func,
		struct_type,
		variable,
	};
	using id_info = std::pair <id_type, int >;
	std::string scope_name;
	using handle_scope = std::shared_ptr<scope>;
	std::vector<handle_scope> inner;
	handle_scope father;
	scope(handle_scope hs,std::string const& sn) : father(hs), scope_name(sn) {}
	handle_scope create_new_scope(std::string const& name) {
		handle_scope handle = std::make_shared<scope>
					(shared_from_this(), scope_name + "::" + name);
		inner.push_back(handle);
		return handle;
	}
	std::map<std::string, id_info> id_map;
	void insert_new_id(std::string const& id,int pos, id_type ty) {
		id_map.emplace(id, std::make_pair(ty, pos));
	}
	id_type get_type_of_id(int id, lex_data const& data) {
		return id_map[get_name_of_now(id,data)].first;
	}
	int get_index(int id, lex_data const& data) {
		return id_map[get_name_of_now(id, data)].second;
	}

	handle_scope find_handle_of_id(int id, lex_data const& data) {
		auto it = id_map.find(get_name_of_now(id, data));
		if(it!= id_map.end())
			return shared_from_this();
		if(father) 
			return father->find_handle_of_id(id,data);
		return nullptr;
	}
};


struct func_def {
	std::vector<std::pair <int, bool>> params;
	std::vector<int> param_offset;
	int def_pos, stack_size;
	int return_type;
	std::map<int, int> id_to_param;
	explicit func_def(int ty_id):return_type(ty_id), def_pos(-1) {}
	bool has_def() { return def_pos >= 0; }
	bool add_param(int str, int type_id,bool arr) {
		if (set_contains(id_to_param, str))return false;
		params.emplace_back(type_id,arr);
		id_to_param[str] = params.size() - 1;
		return true;
	}
};

struct struct_def {
	std::vector<std::pair<int,int>> members;
	std::vector<int> member_offset;
	int struct_size;
	bool is_union;
	struct_def(bool is_union=false): is_union(is_union){}
	std::map<std::string, int> id_to_member;
	int find_member(std::string const& str) {
		auto it=id_to_member.find(str);
		if (it == id_to_member.end())return -1;
		return it->second;
	}
	bool add_member(std::string const &str, std::pair<int, int> type_id) {
		if(set_contains(id_to_member,str))return false;
		members.push_back(type_id);
		id_to_member[str] = members.size() - 1;
		return true;
	}
};

template<class T>
using with_scope = std::pair<T, scope::handle_scope>;

struct symbols {
	// type_id , arr
	using type = std::pair<int, int>;
	// type , lvalue
	using var_def = std::pair<type, bool>;
	static const int
		none = -1,
		void_type = 0,
		char8 = 1,
		uchar8 = 2,
		int16 = 3,
		uint16 = 4,
		int32 = 5,
		uint32 = 6,
		float32 = 7,
		int64 = 8,
		uint64 = 9,
		float64 = 10,
		struct_type = 11;

	static int struct_id(int now) {
		return struct_type + now;
	}
	static int struct_id_pos(int now) {
		return now - struct_type;
	}
	static bool is_struct(int i) {
		return i >= struct_type;
	}

	static void debug_single_quat(parser::quat_type const & qt, labels const & label_lst, lex_data const & data);
	static void debug_quat(std::vector<parser::quat_type> const & quats, labels const & label_lst, lex_data const & data);
	static bool is_int (int ty) {
		return ty <= uint64 && ty >= int16;
	}
	static bool is_float(int ty) {
		return ty == float32 || ty == float64;
	}
	static bool is_char(int ty) {
		return ty == char8 || ty == uchar8;
	}
	static bool is_int_or_char (int ty) {
		return is_int(ty) || is_char(ty);
	}
	static bool is_basic_type(int ty) {
		return ty > void_type&& ty < struct_type;
	}
	static bool is_void(int ty) { return void_type == ty; }
	/*
	 * return number: 
	 *	0 : tyb cast to tya
	 *	1 : tya cast to tyb 
	 *	2 : no type cast
	 */
	static constexpr  int tyb_to_tya = 0,
		tya_to_tyb = 1,
		no_type_cast = 2;
	int simple_type_cast(int tya,int tyb) {
		if (tya > tyb)return tyb_to_tya;
		else if (tya == tyb)return no_type_cast;
		else return tya_to_tyb;
	}
	// <id , <id_type, index> >
	std::vector<func_def> func_list;
	std::vector<struct_def> struct_list;
	std::vector<with_scope<var_def>>var_list;

	int new_var(int ty_id,int arr_size, bool is_lvalue,scope::handle_scope handle) {
		var_list.push_back({ { {ty_id,arr_size},is_lvalue }, handle});
		return var_list.size() - 1;
	}
	int new_struct() {
		struct_list.push_back(struct_def());
		return struct_list.size() - 1;
	}
	int new_func(int ty_id) {
		func_list.push_back(func_def(ty_id));
		return func_list.size() - 1;
	}
	bool is_tmp_var(int id) {
		return (id >= tmp_var_begin);
	}

	bool is_const(int id, lex_data const& data) {
		if (id < 0 || id >= data.lex_result.size())return false;
		switch (data.get_type_token(id)) {
		case type_token::string_literal:
		case type_token::int_literal:
		case type_token::double_literal:
		case type_token::char_literal:
			return true;
		}
		return false;
	}


	symbols::type get_const_type(int id, lex_data const& data) {
		switch (data.get_type_token(id)) {
		case type_token::string_literal:
			return { symbols::char8,data.get_str(id).size() };
		case type_token::int_literal:
			return { symbols::int64,0 };
		case type_token::double_literal:
			return { symbols::float64,0 };
		case type_token::char_literal:
			return { symbols::char8, 0 };
		}
	}

	int curr_call_id, curr_struct, curr_push_order, curr_init_list,tmp_var_cnt;
	const int tmp_var_begin;
	lex_data const& data;
	scope::handle_scope root_scope,h_curr;
	int binocular_type_cast(type , type , quat_op op);
	void monocular_type_check(type ty, quat_op op);
	void assign_type_check(type lhs, type rhs, int atype);
	bool can_cast_to_bool(type ty) {
		return is_basic_type(ty.first) && !ty.second;
	}
	std::vector<parser::quat_type> quats;
	void check_scope(scope::handle_scope hscope, int id);
	void handle_single_quat(parser::quat_type const & qt, lex_data const & data);
	symbols(parser const&p);

};