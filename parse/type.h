#pragma once
#include "graph.h"
#include "parse.h"


struct var_scope {
	std::vector<int> id_set;
	using handle_scope = std::shared_ptr<var_scope>;
	std::vector<handle_scope> inner;
	std::shared_ptr<var_scope> father;
	var_scope(handle_scope hs) : father(hs) {}
};

struct types {
	using type = std::pair<int, int>;
	static const int
		none = -1,
		void_type = 0,
		int16 = 1,
		int32 = 2,
		int64 = 3,
		uint16 = 4,
		uint32 = 5,
		uint64 = 6,
		char8 = 7,
		uchar8 = 8,
		float32 = 9,
		float64 = 10,
		type_struct = 11;
	enum id_type {
		func,
		struct_type,
		variable,
		param,
	};
	using id_full_type = std::pair<id_type, type>;
	int struct_cnt;
	static int struct_id(int now) {
		return type_struct + now;
	}
	static int struct_data_rank(int now) {
		return now - type_struct;
	}
	static bool is_struct(int i) {
		return i >= type_struct;
	}
	static void debug_single_quat(parser::quat_type const & qt, labels const & label_lst, lex_data const & data);
	static void debug_quat(std::vector<parser::quat_type> const & quats, labels const & label_lst, lex_data const & data);
};