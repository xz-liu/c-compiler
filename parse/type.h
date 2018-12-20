#pragma once
#include "graph.h"
#include "parse.h"
struct symbols;
struct scope
	:public std::enable_shared_from_this<scope> {
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
	scope(handle_scope hs, std::string const& sn) : father(hs), scope_name(sn) {}
	handle_scope create_new_scope(std::string const& name) {
		handle_scope handle = std::make_shared<scope>
			(shared_from_this(), scope_name + "::" + name);
		inner.push_back(handle);
		return handle;
	}
	std::map<std::string, id_info> id_map;
	void insert_new_id(std::string const& id, int pos, id_type ty) {
		id_map.emplace(id, std::make_pair(ty, pos));
	}
	id_type get_type_of_id(int id, lex_data const& data) {
		return id_map[get_name_of_now(id, data)].first;
	}
	int get_index(int id, lex_data const& data) {
		return id_map[get_name_of_now(id, data)].second;
	}

	handle_scope find_handle_of_id(int id, lex_data const& data) {
		auto it = id_map.find(get_name_of_now(id, data));
		if (it != id_map.end())
			return shared_from_this();
		if (father)
			return father->find_handle_of_id(id, data);
		return nullptr;
	}
	void debug(std::string prefix="") {
		using std::cout;
		using std::endl;
		cout << prefix << scope_name << "{" << endl;
		prefix.push_back('\t');
		for (auto && x: id_map) {
			cout << prefix << x.first << ":";
			switch (x.second.first) {
			case struct_type:
				cout << "STRUCT ," << x.second.second << endl;
				break;
			case func:
				cout << "FUNCTION ," << x.second.second << endl;
				break;
			case variable:
				cout << "VARIABLE ," << x.second.second << endl;
				break;
			}
		}
		for(auto&& ch:inner) {
			ch->debug(prefix);
		}
		prefix.pop_back();
		cout << prefix << "}" << endl;

	}
};


struct func_def {
	std::vector<std::pair <int, bool>> params;
	std::vector<int> param_offset;
	int def_pos, stack_size;
	int return_type;
	scope::handle_scope function_scope;
	std::map<int, int> id_to_param;
	explicit func_def(int ty_id,int def_pos, scope::handle_scope f_scope) 
		:return_type(ty_id), def_pos(def_pos),stack_size(0), function_scope(f_scope){}
	bool has_def() { return def_pos >= 0; }
	bool add_param(int str, int type_id, bool arr,
		symbols const& sym);
	void debug(symbols & sym);
};

struct struct_def {
	std::vector<std::pair<int, int>> members;
	std::vector<int> member_offset;
	int struct_size;
	bool is_union;
	struct_def(bool is_union = false) : is_union(is_union),struct_size(0) {}
	std::map<std::string, int> id_to_member;
	int find_member(std::string const& str) {
		auto it = id_to_member.find(str);
		if (it == id_to_member.end())return -1;
		return it->second;
	}
	bool add_member(std::string const &str, std::pair<int, int> type_id,
		symbols & sym);
	void debug(symbols& sym);
};

template<class T>
using with_scope = std::pair<T, scope::handle_scope>;

struct symbols {
	// type_id , arr
	using type = std::pair<int, int>;
	// type , lvalue
	using var_type = std::pair<type, bool>;
	using var_def = with_scope<var_type>;
	using quat = std::pair<parser::quat_type, scope::handle_scope>;
	static constexpr int
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
	static constexpr int pointer_size = 4;

	void debug_var(with_scope<var_type> const &v) const{
		std::cout << "<<<" << get_type_name(v.first.first.first, data) << ", "
			<< v.first.first.second << ">, " << std::boolalpha << v.first.second << ">, "
			<< v.second->scope_name << ">" << std::endl;
	}
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
	static void debug_quat(std::vector<quat> const & quats, labels const & label_lst, lex_data const & data);
	static void debug_single_quat(quat const & qt, labels const & label_lst, lex_data const & data);
	static bool is_int(int ty) {
		return ty <= uint64 && ty >= int16;
	}
	static bool is_float(int ty) {
		return ty == float32 || ty == float64;
	}
	static bool is_char(int ty) {
		return ty == char8 || ty == uchar8;
	}
	static bool is_int_or_char(int ty) {
		return is_int(ty) || is_char(ty);
	}
	static bool is_basic_type(int ty) {
		return ty > void_type&& ty < struct_type;
	}
	static bool is_void(int ty) { return void_type == ty; }

	static bool same_cat_type(int ty1, int ty2) {
		return (is_int_or_char(ty1) && is_int_or_char(ty2)) ||
			(is_float(ty1) && is_float(ty2));
	}
	int get_type_size(type const&ty) const {
		int base, num = ty.second;
		if (num <= 1)num = 1;
		if (is_basic_type(ty.first))base = get_basic_type_size(ty.first);
		else base = get_struct_type_size(ty.first);
		if (base >= 0)return base*num;
		else return -1;
	}
	int get_struct_type_size(int ty) const{
		auto hscope = root_scope->find_handle_of_id(struct_id_pos(ty), data);
		if(hscope) {
			int index = hscope->get_index(struct_id_pos(ty), data);
			return struct_list[index].struct_size;
		}
		else { return -1; }
	}
	static int get_basic_type_size(int ty) {
		if (is_basic_type(ty)) {
			switch (ty) {
			case char8:
			case uchar8:
				return 1;
			case int16:
			case uint16:
				return 2;
			case int32:
			case uint32:
			case float32:
				return 4;
			case float64:
			case int64:
			case uint64:
				return 8;
			}
		}
		return -1;
	}
	
	static bool can_cast_to_bool(type ty) {
		return is_basic_type(ty.first) && !ty.second;
	}
	/*
	 * return number:
	 *	0 : tyb cast to tya
	 *	1 : tya cast to tyb
	 *	2 : no type cast
	 */
	static constexpr  int tyb_to_tya = 0,
		tya_to_tyb = 1,
		no_type_cast = 2;
	static int simple_type_cast(int tya, int tyb) {
		if (tya > tyb)return tyb_to_tya;
		else if (tya == tyb)return no_type_cast;
		else return tya_to_tyb;
	}
	// <id , <id_type, index> >
	std::vector<func_def> func_list;
	std::vector<struct_def> struct_list;
	std::vector<var_def>var_list;

	int new_var(int ty_id, int arr_size, bool is_lvalue, scope::handle_scope handle) {
		var_list.push_back({ { {ty_id,arr_size},is_lvalue }, handle });
		return var_list.size() - 1;
	}
	int new_struct(bool is_union) {
		struct_list.push_back(struct_def(is_union));
		return struct_list.size() - 1;
	}
	int new_func(int ty_id,int def_pos, scope::handle_scope hs) {
		func_list.push_back(func_def(ty_id,def_pos,hs));
		return func_list.size() - 1;
	}
	bool is_tmp_var(int id) {
		return (id >= tmp_var_begin);
	}

	bool is_const(int id)const { return is_const(id, data); }
	bool is_const(int id, lex_data const& data) const{
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
	scope::handle_scope find_handl_of_id(scope::handle_scope curr,int id)const {
		return curr->find_handle_of_id(id, data);
	}
	type get_const_type(int id) const { return get_const_type(id, data); }
	static type get_const_type(int id, lex_data const& data) {
		switch (data.get_type_token(id)) {
		case type_token::string_literal:
			return { symbols::char8,data.get_str(id).size()+1 };
		case type_token::int_literal:
			return { symbols::int64,0 };
		case type_token::double_literal:
			return { symbols::float64,0 };
		case type_token::char_literal:
			return { symbols::char8, 0 };
		}
		return { symbols::none ,0 };
	}

	int curr_call_id, curr_struct,curr_func, curr_push_order, curr_init_list, tmp_var_cnt;
	const int tmp_var_begin;
	lex_data const& data;
	scope::handle_scope root_scope, h_curr;
	int binocular_type_cast(type, type, quat_op op);
	void monocular_type_check(type ty, quat_op op);
	void assign_type_check(type lhs, type rhs, int atype);

	std::vector<quat> quats;

	//void check_scope(scope::handle_scope hscope, int id);
	void handle_single_quat(parser::quat_type const & qt, lex_data const & data,int quat_pos);
	symbols(parser const&p);
	void debug() {
		for (int i = 0; i<var_list.size(); i++) {
			std::cout << "VAR_LIST[" << i << "]:";
			debug_var(var_list[i]);
		}
		for (int i = 0; i<struct_list.size(); i++) {
			std::cout << "STRUCT_LIST[" << i << "]:";
			struct_list[i].debug(*this);
		}
		for (int i = 0; i<func_list.size(); i++) {
			std::cout << "FUNC_LIST[" << i << "]:";
			func_list[i].debug(*this);
		}
		root_scope->debug("");	
	}
	
	type get_var_type(int id,scope::handle_scope hscope) {
		return var_list[hscope->find_handle_of_id(id, data)->get_index(id, data)].first.first;
	}

	std::string get_id_name(int id) {
		return get_name_of_now(id, data);
	}
	scope::handle_scope get_handle(int id, scope::handle_scope curr_handle) {
		return curr_handle->find_handle_of_id(id, data);
	}
	
	int get_id_index(int id, scope::handle_scope curr) {
		return curr->get_index(id, data);
	}
	
	scope::id_type get_id_cat(int id, scope::handle_scope curr) {
		return curr->get_type_of_id(id, data);
	}

	void testtest(int i) {
		quat qt = quats[i];
		quat_op op = qt.first.first;
		std::array<int, 3> &qv = qt.first.second;
		if (op == quat_op::label) {
			//label 
			int pos = qv[0];
		} else if (op == quat_op::add) {
			// lhs,rhs,to 
			scope::handle_scope scopes[3]{ find_handl_of_id(qt.second,qv[0]),
							find_handl_of_id(qt.second,qv[1]),
							find_handl_of_id(qt.second,qv[2]) };
			var_def vars[3];
			for(int v=0;v<3;v++) {
				vars[v] = var_list[scopes[v]->get_index(qv[v], data)];
			}
			int size=get_type_size(vars[0].first.first);
			//<int, 30> 4*30=120
		}else if(op == quat_op::newvar) {
			// id, type, array
			
		}
	}

};